#include <cstdio>
#include <cstdlib>
#include <cstring>
/* ����Ԫ�����Ͷ��� */
typedef int QElemType;
// ����Ԫ�ؽṹ
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;
// ���нṹ
typedef struct
{
    QueuePtr front; // ��ͷָ��
    QueuePtr rear;  // ��βָ��
} LinkQueue;        // ���е���ʽ�洢��ʾ
/*
 * ��ʼ��
 *
 * ����һ���յ����ӡ�
 * ��ʼ���ɹ��򷵻�OK�����򷵻�ERROR��
 *
 *��ע��
 * ����Ķ��д���ͷ���
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
 * �п�
 *
 * �ж��������Ƿ������Ч���ݡ�
 *
 * ����ֵ��
 * TRUE : ����Ϊ��
 * FALSE: ���Ӳ�Ϊ��
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
 * ���
 *
 * ��Ԫ��e��ӵ�����β����
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
 * ����
 *
 * �Ƴ�����ͷ����Ԫ�أ�����洢��e�С�
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
