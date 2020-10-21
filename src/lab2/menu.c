/**************************************************************************************************/
/* Copyright (C) mc2lab.com, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  Mengning                                                             */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/08/31                                                           */
/*  DESCRIPTION           :  This is a menu program                                               */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning, 2014/08/31
 *
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char cmd[128];
    while(1)
    {
        scanf("%s", cmd);
        if(strcmp(cmd, "help") == 0)
        {
            printf("This is help cmd!\n");
        }
        else if(strcmp(cmd, "quit") == 0)
        {
            exit(0);
        }
        else
        {
            printf("Wrong cmd!\n");
        }
    }
}
