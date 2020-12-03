#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int ElemType;

typedef struct LNode
{
    ElemType data;      // ���ݽ��
    struct LNode *next; // ָ����һ������ָ��
} LNode;

// ָ���������ָ��
typedef LNode *LinkList;

/*
 * ��ʼ��
 *
 * ��ʼ���ɹ��򷵻�OK�����򷵻�ERROR��
 */
bool InitList(LinkList *L)
{
    (*L) = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL)
    {
        exit(-2);
    }

    (*L)->next = NULL;

    return true;
}

/*
 * ����(�ṹ)
 *
 * �ͷ�������ռ�ڴ档
 */
bool DestroyList(LinkList *L)
{
    LinkList p;

    // ȷ������ṹ����
    if (L == NULL || *L == NULL)
    {
        return false;
    }

    p = *L;

    while (p != NULL)
    {
        p = (*L)->next;
        free(*L);
        (*L) = p;
    }

    *L = NULL;

    return true;
}

/*
 * �ÿ�(����)
 *
 * ������Ҫ�ͷ������з�ͷ��㴦�Ŀռ䡣
 */
bool ClearList(LinkList L)
{
    LinkList pre, p;

    // ȷ���������
    if (L == NULL)
    {
        return false;
    }

    p = L->next;

    // �ͷ����������н����ռ�ڴ�
    while (p != NULL)
    {
        pre = p;
        p = p->next;
        free(pre);
    }

    L->next = NULL;

    return true;
}

/*
 * ����
 *
 * �����������׸���e����Compare��ϵ��Ԫ��λ��
 * ���������������Ԫ�أ��򷵻�0��
 *
 *����ע��
 * Ԫ��e��Compare�����ڶ����β�
 */
int LocateElem(LinkList L, ElemType e, bool(Compare)(ElemType, ElemType))
{
    int i;
    LinkList p;

    // ȷ����������Ҳ�Ϊ�ձ�
    if (L == NULL || L->next == NULL)
    {
        return 0;
    }

    i = 1;       // i�ĳ�ֵΪ��1��Ԫ�ص�λ��
    p = L->next; // p�ĳ�ֵΪ��1��Ԫ�ص�ָ��

    while (p != NULL && !Compare(p->data, e))
    {
        i++;
        p = p->next;
    }

    if (p != NULL)
    {
        return i;
    }
    else
    {
        return 0;
    }
}
/*
 * ����
 * 
 * �������i��λ���ϲ���e������ɹ��򷵻�OK�����򷵻�ERROR��
 * 
 */
bool ListInsert(LinkList L, int i, ElemType e)
{
    LinkList p, s;
    int j;

    // ȷ�������
    if (L == NULL)
    {
        return false;
    }

    p = L;
    j = 0;

    // Ѱ�ҵ�i-1����㣬�ұ�֤�ý�㱾��ΪNULL
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        ++j;
    }

    // ���������ͷ�ˣ�����i��ֵ���Ϲ�(����i<=0)��˵��û�ҵ��Ϻ�Ŀ��Ľ��
    if (p == NULL || j > i - 1)
    {
        return false;
    }

    // �����½��
    s = (LinkList)malloc(sizeof(LNode));
    if (s == NULL)
    {
        exit(-2);
    }
    s->data = e;
    s->next = p->next;
    p->next = s;

    return true;
}

// �ж����Ա�������Ԫ���Ƿ����
bool Equal(ElemType e1, ElemType e2)
{
    return e1 == e2 ? true : false;
}
