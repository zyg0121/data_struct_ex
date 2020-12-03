#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef int ElemType;

typedef struct LNode
{
    ElemType data;      // 数据结点
    struct LNode *next; // 指向下一个结点的指针
} LNode;

// 指向单链表结点的指针
typedef LNode *LinkList;

/*
 * 初始化
 *
 * 初始化成功则返回OK，否则返回ERROR。
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
 * 销毁(结构)
 *
 * 释放链表所占内存。
 */
bool DestroyList(LinkList *L)
{
    LinkList p;

    // 确保链表结构存在
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
 * 置空(内容)
 *
 * 这里需要释放链表中非头结点处的空间。
 */
bool ClearList(LinkList L)
{
    LinkList pre, p;

    // 确保链表存在
    if (L == NULL)
    {
        return false;
    }

    p = L->next;

    // 释放链表上所有结点所占内存
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
 * 查找
 *
 * 返回链表中首个与e满足Compare关系的元素位序。
 * 如果不存在这样的元素，则返回0。
 *
 *【备注】
 * 元素e是Compare函数第二个形参
 */
int LocateElem(LinkList L, ElemType e, bool(Compare)(ElemType, ElemType))
{
    int i;
    LinkList p;

    // 确保链表存在且不为空表
    if (L == NULL || L->next == NULL)
    {
        return 0;
    }

    i = 1;       // i的初值为第1个元素的位序
    p = L->next; // p的初值为第1个元素的指针

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
 * 插入
 * 
 * 向链表第i个位置上插入e，插入成功则返回OK，否则返回ERROR。
 * 
 */
bool ListInsert(LinkList L, int i, ElemType e)
{
    LinkList p, s;
    int j;

    // 确保链表存
    if (L == NULL)
    {
        return false;
    }

    p = L;
    j = 0;

    // 寻找第i-1个结点，且保证该结点本身不为NULL
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        ++j;
    }

    // 如果遍历到头了，或者i的值不合规(比如i<=0)，说明没找到合乎目标的结点
    if (p == NULL || j > i - 1)
    {
        return false;
    }

    // 生成新结点
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

// 判断线性表中两个元素是否相等
bool Equal(ElemType e1, ElemType e2)
{
    return e1 == e2 ? true : false;
}
