#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int Quit()
{
    /* add XXX clean ops */
    exit(0);
}

int main()
{

    MenuConfig("version", "XXX V1.0(Menu program v1.0 inside)", NULL);
    MenuConfig("quit", "Quit from XXX", Quit);
    
    ExecuteMenu();
}

