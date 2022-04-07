
#include <pthread.h>

/*
 * LinkTable Node Type
 */
struct LinkTableNode
{
    struct LinkTableNode * pNext;
};
/*
 * LinkTable Type
 */
struct LinkTable
{
    struct LinkTableNode *pHead;
    struct LinkTableNode *pTail;
    int			SumOfNode;
    pthread_mutex_t mutex;

};