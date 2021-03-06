
/********************************************************************/
/* Copyright (C) SSE-USTC, 2012-2013                                */
/*                                                                  */
/*  FILE NAME             :  testlinktabe.c                         */
/*  PRINCIPAL AUTHOR      :  Mengning                               */
/*  SUBSYSTEM NAME        :  LinkTable                              */
/*  MODULE NAME           :  LinkTable                              */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2012/12/30                             */
/*  DESCRIPTION           :  test of Link Table                     */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning, 2012/12/30
 * Verified callback and head/next for search by Mengning, 2012/09/17
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"linktable.h"

#define debug printf  

typedef struct Node
{
    tLinkTableNode head;
    int data;
}tNode;

tNode * Search(tLinkTable *pLinkTable);

int main()
{
    int i;
    tLinkTable * pLinkTable = CreateLinkTable();
    if (pLinkTable == NULL)
    {
        printf("CreateLinkTable Error!\n");
        exit(0);
    }
    for(i = 0; i < 10; i++)
    {
        tNode* pNode = (tNode*)malloc(sizeof(tNode));
        pNode->data = i;
        debug("AddLinkTableNode\n");
        AddLinkTableNode(pLinkTable, (tLinkTableNode *)pNode);
    }
    /* search one by one */
    tNode * pTempNode = Search(pLinkTable);
    printf("%d\n", pTempNode->data);
    debug("DelLinkTableNode\n");
    DelLinkTableNode(pLinkTable, (tLinkTableNode *)pTempNode);
    free(pTempNode);
    DeleteLinkTable(pLinkTable);
}

tNode * Search(tLinkTable *pLinkTable)
{
    debug("Search GetLinkTableHead\n");
    tNode * pNode = (tNode*)GetLinkTableHead(pLinkTable);
    while(pNode != NULL)
    {
        if(pNode->data == 5)
        {
            return  pNode;  
        }
        debug("GetNextLinkTableNode\n");
        pNode = (tNode*)GetNextLinkTableNode(pLinkTable, (tLinkTableNode *)pNode);
    }
    return NULL;
}
