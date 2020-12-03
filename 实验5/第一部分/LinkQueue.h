#include <cstdio>
#include <cstdlib>
#include <cstring>
/* 链队元素类型定义 */
typedef int QElemType;
// 队列元素结构
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;
// 队列结构
typedef struct
{
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
} LinkQueue;        // 队列的链式存储表示
/*
 * 初始化
 *
 * 构造一个空的链队。
 * 初始化成功则返回OK，否则返回ERROR。
 *
 *【注】
 * 这里的队列带有头结点
 */
bool InitQueue(LinkQueue *Q)
{
    if (Q == NULL)
    {
        return false;
    }

    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front)
    {
        exit(-2);
    }

    Q->front->next = NULL;

    return true;
}
/*
 * 判空
 *
 * 判断链队中是否包含有效数据。
 *
 * 返回值：
 * TRUE : 链队为空
 * FALSE: 链队不为空
 */
bool QueueEmpty(LinkQueue Q)
{
    if (Q.front == Q.rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
 * 入队
 *
 * 将元素e添加到队列尾部。
 */
bool EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr p;
    if (Q == NULL || Q->front == NULL)
    {
        return false;
    }
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
    {
        exit(-2);
    }
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return true;
}
/*
 * 出队
 *
 * 移除队列头部的元素，将其存储到e中。
 */
bool DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;

    if (Q == NULL || Q->front == NULL || Q->front == Q->rear)
    {
        return false;
    }
    p = Q->front->next;
    *e = p->data;

    Q->front->next = p->next;
    if (Q->rear == p)
    {
        Q->rear = Q->front;
    }
    free(p);
    return true;
}
