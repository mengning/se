### Docker

在WSL Ubuntu-20.04环境下


```
wsl.exe --install -d Ubuntu-20.04
正在安装: Ubuntu 20.04 LTS
已安装 Ubuntu 20.04 LTS。
正在启动 Ubuntu 20.04 LTS...
Installing, this may take a few minutes...
Please create a default UNIX user account. The username does not need to match your Windows username.
For more information visit: https://aka.ms/wslusers
Enter new UNIX username: ubuntu
New password: 
Retype new password: 
passwd: password updated successfully
Installation successful!
To run a command as administrator (user "root"), use "sudo <command>".
See "man sudo_root" for details.

Welcome to Ubuntu 20.04.6 LTS (GNU/Linux 5.15.153.1-microsoft-standard-WSL2 x86_64)
```


* 安装Docker


```
$ sudo apt update
$ sudo apt install docker.io
```


在mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04容器环境下安装docker.io无法正常启动Docker服务。

* 使用Docker


```
$ sudo docker pull mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04
$ sudo docker images
$ sudo docker ps -a
$ sudo docker run -it mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04

```

另外还有docker start/stop、rm -f、diff、commit，docker login、tag、pull/push等

sudo docker rm -f $(sudo docker ps -aq) 清理掉所有容器
sudo docker system df 查看存储占用

* 制作容器镜像

可以使用`Dockerfile`制作容器镜像，


```
FROM mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04

# 安装所需的工具
RUN apt-get update &&           \
    apt-get install -y          \
        build-essential         \
        qemu-system-x86         \
        libncurses5-dev         \
        bison                   \
        flex                    \
        libssl-dev              \
        libelf-dev              \
	gdb

CMD ["bash"]
```

如下命令：

```shell
sudo apt install docker.io
# 根据需要安装配置Docker，也可以在本地重新打开项目，然后使用Docker命令
docker build -f Dockerfile -t ubuntu20.04-linuxkernel .
```

也可以将当前正在运行的容器直接保存为容器镜像

```shell
# 确保当前容器正在运行。可以使用以下命令列出当前正在运行的容器：
docker ps

# 获取当前容器的容器 ID，可以通过上一步骤中的输出或者以下命令获取：
docker ps -aqf "name=your_container_name"

# 使用以下命令将当前容器保存为镜像：
docker commit container_id ubuntu20.04-linuxkernel

其中，container_id 为docker ps中获取的容器ID。
```

## 上传开发环境

将构建好的容器镜像上传到镜像仓库中，供其他开发者使用。镜像仓库默认是Docker官方的DockerHub，这里使用devstar.cn镜像仓库，`mengning`是镜像仓库的账号名称。

```shell
docker login devstar.cn # 这里镜像仓库的账号和密码
docker tag ubuntu20.04-linuxkernel devstar.cn/mengning/ubuntu20.04-linuxkernel:v1.0 # 注意升级tag版本
docker push devstar.cn/mengning/ubuntu20.04-linuxkernel:v1.0
docker tag ubuntu20.04-linuxkernel devstar.cn/mengning/ubuntu20.04-linuxkernel
docker push devstar.cn/mengning/ubuntu20.04-linuxkernel # 更新latest
```

这样我们就可以在.devcontainer/devcontainer.json或Dockerfile中使用镜像名称devstar.cn/mengning/ubuntu20.04-linuxkernel

* Docker镜像和容器的存储

/var/lib/docker/ 目录是默认的镜像存储位置。容器的文件系统仍然在 /var/lib/docker/ 目录下，通常位于 /var/lib/docker/containers/ 目录中。

如果需要改变 Docker 的默认存储位置，您可以通过修改 Docker 的配置文件来实现。例如，在 Linux 上，您可以编辑 /etc/docker/daemon.json 文件（该文件可能需要手动创建），并设置 data-root 参数，如下所示：


```
{
  "data-root": "/home/ubuntu/docker"
}
```

更改后，重新启动 Docker 服务使其生效：


```
$ sudo systemctl restart docker
$ sudo docker images
REPOSITORY   TAG       IMAGE ID   CREATED   SIZE
$ sudo docker ps
CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES
$ sudo docker pull mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04
dev-ubuntu-20.04: Pulling from devcontainers/base
560c024910be: Pull complete 
c0f0b693a55b: Pull complete 
a9ab5be1c5fc: Pull complete 
b963894df48a: Pull complete 
787946ab6d9f: Pull complete 
2244093d2e4a: Pull complete 
21369f4c9cbf: Pull complete 
16c0e6832523: Pull complete 
Digest: sha256:a179f312e60ec11afa682c099e4df6ffc34d310837e7f448aedd7efa32c539dc
Status: Downloaded newer image for mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04
mcr.microsoft.com/devcontainers/base:dev-ubuntu-20.04
$ sudo docker images
REPOSITORY                             TAG                IMAGE ID       CREATED      SIZE
mcr.microsoft.com/devcontainers/base   dev-ubuntu-20.04   a3c24b704026   4 days ago   719MB
~/docker$ sudo ls
buildkit  containers  engine-id  image  network  overlay2  plugins  runtimes  swarm  tmp  volumes
```

每启动（run or start）一个容器消耗镜像大小的存储空间，停止（stop）容器后容器似乎并不占用空间（用户在容器中增加内容会以增量内容大小占用存储空间）。
给一个已有的镜像设置新的名称（tag）并不会增加占用存储空间，将容器提交为（commit）镜像并不会增加占用存储空间。

```
ubuntu@DESKTOP-IBF51L8:~/docker$ sudo du -sh ~/docker
743M    /home/ubuntu/docker
ubuntu@DESKTOP-IBF51L8:~/docker$ sudo du -sh ~/docker
1.5G    /home/ubuntu/docker
ubuntu@DESKTOP-IBF51L8:~/docker$ sudo du -sh ~/docker
2.2G    /home/ubuntu/docker
ubuntu@DESKTOP-IBF51L8:~/docker$ sudo du -sh ~/docker
2.9G    /home/ubuntu/docker
```

每启动（run or start）一个容器消耗镜像大小的存储空间（du -sh），但是docker system df显示容器并没有占用存储空间，为什么？


```
$ sudo docker system df
TYPE            TOTAL     ACTIVE    SIZE      RECLAIMABLE
Images          2         2         771.5MB   718.5MB (93%)
Containers      2         0         0B        0B
Local Volumes   0         0         0B        0B
Build Cache     0         0         0B        0B
```

应该是du -sh命令重复统计了overlay文件系统的只读层，通过du -sh --one-file-system 命令可以排除重复挂载的只读层，通过df命令也侧面印证确实没有像du -sh 统计数据那样被占用。

```
$ sudo du -sh --one-file-system ~/docker
794M    /home/ubuntu/docker
```

* 迁移镜像和容器数据


```
sudo systemctl stop docker
sudo mv /var/lib/docker/ /home/ubuntu/workspace
sudo vi /etc/docker/daemon.json

{
  "data-root": "/home/ubuntu/workspace/docker"
}

sudo systemctl restart docker
```

