## git团队开发操作流程

* [代码中的软件工程](https://gitee.com/mengning997/se) - 五大场景玩转 Git, 我们采用git用法场景三和场景四的工作流程
* 一、克隆或同步最新的代码到本地存储库
```
git clone https://DOMAIN_NAME/YOUR_NAME/REPO_NAME.git
git pull
```
* 二、为自己的工作创建一个分支，该分支应该只负责单一功能模块或代码模块的版本控制；
```
git checkout -b mybranch
git branch
```
* 三、在该分支上完成某单一功能模块或代码模块的开发工作；多次进行如下操作：
```
git add FILES
git commit -m "commit log"
```
* 四、最后，先切换回master分支，将远程origin/master同步最新到本地存储库，再合并mybranch到master分支，推送到远程origin/master之后即完成了一项开发工作。
```
git checkout master
git pull
git merge --no-ff mybranch
git push
```
* [Linux相关学习资料](https://gitee.com/mengning997/linuxkernel/tree/master/ppt)