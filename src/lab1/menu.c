int main()
{
    while(true)
    {
        scanf(cmd);
        int ret = strcmp(cmd, "help");
        if(ret == 0)
        {
            dosth();
        }
        int ret = strcmp(cmd, "others");
        if(ret == 0)
        {
            dosth();
        }
    }
}
