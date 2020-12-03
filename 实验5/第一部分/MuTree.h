#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdarg>
#include <cctype>
#include "LinkList.h"
#include "LinkQueue.h"

/* 树的最大结点数 */
const int MAX_TREE_SIZE = 1024;

/* 单个结点最大的孩子数量 */
const int MAX_CHILD_COUNT = 8;

/* 树的元素类型定义，这里假设其元素类型为char */
typedef char TElemType;

typedef struct PTNode
{
    TElemType data;
    int parent; // 双亲位置域
} PTNode;

/*
 * 树类型定义
 */
typedef struct
{
    PTNode nodes[MAX_TREE_SIZE]; // 存储树中结点
    int r;                       // 树根位置(索引)
    int n;                       // 树的结点数
} PTree;

/* 树中某个结点的信息 */
typedef struct
{
    int row;        // 当前结点所处的行
    int col;        // 当前结点所处的列
    int childIndex; // 当前结点是第几个孩子
    int firstChild; // 当前结点的第一个孩子在树中的索引
    int lastChild;  // 当前结点的最后一个孩子在树中的索引
} Pos;
/*
 * 初始化
 *
 * 构造空树。
 */
bool InitTree(PTree *T);
/*
 * 销毁
 *
 * 释放树所占内存。
 */
bool DestroyTree(PTree *T);
/*
 * 置空
 *
 * 清理树中的数据，使其成为空树。
 */
bool ClearTree(PTree *T);
/*
 * 创建
 *
 * 按照预设的定义来创建树。
 * 这里约定使用【层序序列】来创建树。
 */
bool CreateTree(PTree *T, char *path);
/*
 * 判空
 *
 * 判断树是否为空树。
 */
bool TreeEmpty(PTree T);
/*
 * 树深
 *
 * 返回树的深度（层数）。
 */
int TreeDepth(PTree T);
/*
 * 取值
 *
 * 返回树中指定结点的值。
 */
TElemType Value(PTree T, TElemType e);
/*
 * 赋值
 *
 * 为树指定的结点赋值。
 */
bool Assign(PTree *T, TElemType e, TElemType value);
/*
 * 根
 *
 * 返回树的根结点。
 */
TElemType Root(PTree T);
/*
 * 双亲
 *
 * 返回树中结点e的双亲结点。
 */
TElemType Parent(PTree T, TElemType e);
/*
 * 孩子数量
 *
 * 返回树T中结点e的孩子数量。
 */
int ChildCount(PTree T, TElemType e);
/*
 * 孩子
 *
 * 返回树中结点e的第i个孩子。
 */
TElemType Child(PTree T, TElemType e, int i);
/*
 * 左兄弟
 *
 * 返回树中结点e的左兄弟结点。
 *
 *【注】
 * 由于树的结点可能会包含多个孩子，
 * 因此这里的左兄弟特指左边紧邻该结点的兄弟。
 */
TElemType LeftSibling(PTree T, TElemType e);
/*
 * 右兄弟
 *
 * 返回树中结点e的右兄弟结点。
 *
 *【注】
 * 由于树的结点可能会包含多个孩子，
 * 因此这里的右兄弟特指右边紧邻该结点的兄弟。
 */
TElemType RightSibling(PTree T, TElemType e);
/*
 * 插入
 *
 * 将树c插入为树T中p结点的第i个孩子。
 */
bool InsertChild(PTree *T, TElemType p, int i, PTree c);
/*
 * 删除
 *
 * 删除树T中p结点的第i个孩子。
 */
bool DeleteChild(PTree *T, TElemType p, int i);
/*
 * 先序遍历
 */
bool PreOrderTraverse(PTree T, bool(Visit)(TElemType));
/*
 * 后序遍历
 */
bool PostOrderTraverse(PTree T, bool(Visit)(TElemType));
/*
 * 层序遍历
 */
bool LevelOrderTraverse(PTree T, bool(Visit)(TElemType));
// 创建树的内部函数
static void Create(PTree *T, FILE *fp);
// 返回树结点e的索引，如果不存在，返回-1
static int EIndex(PTree T, TElemType e);
// 返回树结点e的第i个孩子索引，如果不存在，返回-1
static int CIndex(PTree T, TElemType e, int i);
// 获取树T的结点信息，具体包含哪些信息，请参照Pos类型的定义
static void getPos(PTree T, Pos pt[]);
// 先序遍历的内部实现
static bool PreTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType));
// 后序遍历的内部实现
static bool PostTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType));
// 输出pos信息
static void printPos(PTree T, Pos pt[]);
// 以图形化形式输出当前结构
void PrintTree(PTree T);
// 图形化输出当前结构内部实现
static void Print(PTree T, Pos pt[], int i);
// 图形化输出树的排列结构
static void PrintFramework(PTree T);
//读取文件信息
int ReadData(FILE *fp, char *format, ...);

bool InitTree(PTree *T)
{
    if (T == NULL)
    {
        return false;
    }

    T->n = 0;

    // 所有数据清零
    memset(T->nodes, 0, sizeof(T->nodes));

    return true;
}

bool DestroyTree(PTree *T)
{
    return false;
}

bool ClearTree(PTree *T)
{
    if (T == NULL)
    {
        return false;
    }

    // 将元素数量归零即可
    T->n = 0;

    // 所有数据清零
    memset(T->nodes, 0, sizeof(T->nodes));

    return true;
}

bool CreateTree(PTree *T, char *path)
{
    FILE *fp;
    int readFromConsole; // 是否从控制台读取数据

    // 如果没有文件路径信息，则从控制台读取输入
    readFromConsole = path == NULL || strcmp(path, "") == 0;

    if (readFromConsole)
    {
        printf("请输入树的元素信息，对于空结点，使用^代替...\n");
        Create(T, NULL);
    }
    else
    {
        // 打开文件，准备读取测试数据
        fp = fopen(path, "r");
        if (fp == NULL)
        {
            return false;
        }
        Create(T, fp);
        fclose(fp);
    }

    return true;
}

bool TreeEmpty(PTree T)
{
    return T.n == 0 ? true : false;
}

int TreeDepth(PTree T)
{
    int k, level;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return 0;
    }

    /*
     * 将k初始化为最后一个结点的位置
     * 由于树的结点按层序存储，故最后存储的结点必定位于最大层
     */
    k = (T.r + T.n - 1) % MAX_TREE_SIZE;
    level = 0;

    do
    {
        level++;
        k = T.nodes[k].parent;
    } while (k != -1);

    return level;
}

TElemType Value(PTree T, TElemType e)
{
    int p;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // 获取结点e的索引
    p = EIndex(T, e);

    // 如果没有找到元素e
    if (p == -1)
    {
        return '\0';
    }
    else
    {
        return T.nodes[p].data;
    }
}

bool Assign(PTree *T, TElemType e, TElemType value)
{
    int p;

    // 遇到空树则无需继续计算
    if (TreeEmpty(*T))
    {
        return false;
    }

    // 获取结点e的索引
    p = EIndex(*T, e);

    // 如果没有找到元素e
    if (p == -1)
    {
        return false;
    }
    else
    {
        // 进行赋值
        T->nodes[p].data = value;
        return true;
    }
}

TElemType Root(PTree T)
{
    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    return T.nodes[T.r].data;
}

TElemType Parent(PTree T, TElemType e)
{
    int p, parent;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // 获取结点e的索引
    p = EIndex(T, e);

    // 如果没有找到元素e
    if (p == -1)
    {
        return '\0';
    }
    else
    {
        parent = T.nodes[p].parent;

        // 根结点无双亲
        if (parent == -1)
        {
            return '\0';
        }
        else
        {
            return T.nodes[parent].data;
        }
    }
}

int ChildCount(PTree T, TElemType e)
{
    int p, k, count;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return -1;
    }

    // 获取结点e的索引
    p = EIndex(T, e);
    // 结点e不存在
    if (p == -1)
    {
        return -1;
    }

    // 查找第一个孩子
    for (k = (p + 1) % MAX_TREE_SIZE; k != (T.r + T.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        if (T.nodes[k].parent == p)
        {
            break;
        }
    }

    count = 0;

    // 统计结点e的孩子数量
    while (k != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[k].parent == p)
    {
        count++;
        k = (k + 1) % MAX_TREE_SIZE;
    }

    return count;
}

TElemType Child(PTree T, TElemType e, int i)
{
    int p;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // i的范围越界
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return '\0';
    }

    // 获取结点e的第i个孩子索引
    p = CIndex(T, e, i);
    // 结点e第i个孩子不存在
    if (p == -1)
    {
        return '\0';
    }

    return T.nodes[p].data;
}

TElemType LeftSibling(PTree T, TElemType e)
{
    int p, ls;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // 获取结点e的索引
    p = EIndex(T, e);
    // 结点e不存在
    if (p == -1)
    {
        return '\0';
    }

    // 假设存在左兄弟
    ls = (p - 1 + MAX_TREE_SIZE) % MAX_TREE_SIZE;

    // 如果该结点有效，且与结点e的双亲相同，说明它是兄弟
    if (ls != p && T.nodes[ls].data != '\0' && T.nodes[ls].parent == T.nodes[p].parent)
    {
        return T.nodes[ls].data;
    }

    return '\0';
}

TElemType RightSibling(PTree T, TElemType e)
{
    int p, rs;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // 获取结点e的索引
    p = EIndex(T, e);
    // 结点e不存在
    if (p == -1)
    {
        return '\0';
    }

    // 假设存在右兄弟
    rs = (p + 1) % MAX_TREE_SIZE;

    // 如果该结点有效，且与结点e的双亲相同，说明它是兄弟
    if (rs != p && T.nodes[rs].data != '\0' && T.nodes[rs].parent == T.nodes[p].parent)
    {
        return T.nodes[rs].data;
    }

    return '\0';
}

bool InsertChild(PTree *T, TElemType p, int i, PTree c)
{
    Pos pt[MAX_TREE_SIZE], pc[MAX_TREE_SIZE];
    int pIndex;
    int lastChild, bound;
    int level;
    int m, n, k;
    int tCur, cCur;

    PTree R;
    int tParent[MAX_TREE_SIZE], cParent[MAX_TREE_SIZE];
    int x, y, z;

    // 如果树为空树则无需继续计算
    if (TreeEmpty(*T) || TreeEmpty(c))
    {
        return false;
    }

    // i的范围过于小
    if (i < 1)
    {
        return false;
    }

    // 获取结点p的索引
    pIndex = EIndex(*T, p);

    // 如果p结点不存在，则返回错误提示
    if (pIndex == -1)
    {
        return false;
    }

    // 计算T中结点的位置信息
    getPos(*T, pt);

    // 结点p最后一个孩子的索引
    lastChild = pt[pIndex].lastChild;

    // i的范围过大
    if (lastChild != -1 && i > pt[lastChild].childIndex + 1)
    {
        return false;
    }

    if (i == 1)
    {
        // 结点p本身是第一个孩子
        if (pt[pIndex].childIndex == 1)
        {
            bound = -1;
        }
        else
        {
            // 从p的左兄弟起，向左查找
            for (k = (pIndex - 1) % MAX_TREE_SIZE; pt[k].lastChild == -1 && pt[k].childIndex != 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // 查找右边界的父结点的索引
            }

            // 已经遍历到该层第一个结点，但该结点仍然没有孩子
            if (pt[k].lastChild == -1)
            {
                bound = -1;
            }
            else
            {
                bound = pt[k].lastChild; // k结点最后一个孩子的索引
            }
        }
    }
    else
    {
        // 结点p没有孩子
        if (lastChild == -1)
        {
            return false;
        }
        else
        {
            for (k = pt[pIndex].lastChild; pt[k].childIndex != i - 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // 查找插入位置的前一个孩子的索引
            }
            bound = k;
        }
    }

    level = pt[pIndex].row + 1; // 待插入的树的根结点所在的行

    // 计算c中结点的位置信息
    getPos(c, pc);
    // 处理新插入的树中各元素的行数
    for (k = c.r; k != (c.r + c.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        pc[k].row += level - 1;
    }

    // tCur指向第level行的第一个结点
    for (tCur = pIndex; tCur != (T->r + T->n) % MAX_TREE_SIZE; tCur = (tCur + 1) % MAX_TREE_SIZE)
    {
        if (pt[tCur].row == level)
        {
            break;
        }
    }

    // cCur指向树c中的根结点，该根结点也应当插入到树T中的level行
    cCur = c.r;

    while (tCur != (T->r + T->n) % MAX_TREE_SIZE && cCur != (c.r + c.n) % MAX_TREE_SIZE)
    {
        // 跳过树T右界的前半部分
        if (bound != -1)
        {
            tCur = (bound + 1) % MAX_TREE_SIZE;
        }

        if (bound == -1)
        {
            m = 0;
        }
        else
        {
            m = pt[bound].col;
        }

        n = 0;

        // 将c插入到T的中间
        while (cCur != (c.r + c.n) % MAX_TREE_SIZE && pc[cCur].row == level)
        {
            // 改变列

            pc[cCur].col += m;
            n++;

            cCur++;
        }

        // 处理T的后半部分
        while (tCur != (T->r + T->n) % MAX_TREE_SIZE && pt[tCur].row == level)
        {

            pt[tCur].col += n;

            tCur++;
        }

        // 计算下一层的边界
        if (bound != -1)
        {
            // 从bound起，向左查找
            for (k = bound; pt[k].lastChild == -1 && pt[k].childIndex != 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // 查找右边界的父结点的索引
            }

            // 已经遍历到该层第一个结点，但该结点仍然没有孩子
            if (pt[k].lastChild == -1)
            {
                bound = -1;
            }
            else
            {
                bound = pt[k].lastChild; // k结点最后一个孩子的索引
            }
        }

        level++;
    }

    // 检验pos信息
    //    printPos(*T, pt);
    //    printPos(c, pc);

    InitTree(&R);

    R.r = T->r;
    n = 0;

    x = T->r; // 遍历T的游标
    y = c.r;  // 遍历c的游标
    z = R.r;  // 遍历R的游标

    while (x != (T->r + T->n) % MAX_TREE_SIZE && y != (c.r + c.n) % MAX_TREE_SIZE)
    {
        if (pt[x].row < pc[y].row || (pt[x].row == pc[y].row && pt[x].col < pc[y].col))
        {

            // 记录结点x的新位置
            tParent[x] = z;

            // 有效元素放到新位置上
            R.nodes[z] = T->nodes[x];

            if (R.nodes[z].parent != -1)
            {
                // 更新父结点位置
                R.nodes[z].parent = tParent[R.nodes[z].parent];
            }

            x = (x + 1) % MAX_TREE_SIZE;
        }
        else if (pt[x].row > pc[y].row || (pt[x].row == pc[y].row && pt[x].col > pc[y].col))
        {
            // 记录结点y的新位置
            cParent[y] = z;

            // 有效元素放到新位置上
            R.nodes[z] = c.nodes[y];

            if (R.nodes[z].parent != -1)
            {
                // 更新父结点位置
                R.nodes[z].parent = cParent[R.nodes[z].parent];
            }
            else
            {
                // 将两棵树连到一起，即树c的根结点的父结点为p
                R.nodes[z].parent = tParent[pIndex];
            }

            y = (y + 1) % MAX_TREE_SIZE;
        }

        z = (z + 1) % MAX_TREE_SIZE;
        n++;
    }

    while (x != (T->r + T->n) % MAX_TREE_SIZE)
    {
        // 记录结点k的新位置
        tParent[x] = z;

        // 有效元素放到新位置上
        R.nodes[z] = T->nodes[x];

        if (R.nodes[z].parent != -1)
        {
            // 更新父结点位置
            R.nodes[z].parent = tParent[R.nodes[z].parent];
        }

        x = (x + 1) % MAX_TREE_SIZE;
        z = (z + 1) % MAX_TREE_SIZE;
        n++;
    }

    while (y != (c.r + c.n) % MAX_TREE_SIZE)
    {
        // 记录结点k的新位置
        cParent[y] = z;

        // 有效元素放到新位置上
        R.nodes[z] = c.nodes[y];

        if (R.nodes[z].parent != -1)
        {
            // 更新父结点位置
            R.nodes[z].parent = cParent[R.nodes[z].parent];
        }
        else
        {
            // 将两棵树连到一起，即树c的根结点的父结点为p
            R.nodes[z].parent = tParent[pIndex];
        }

        y = (y + 1) % MAX_TREE_SIZE;
        z = (z + 1) % MAX_TREE_SIZE;
        n++;
    }

    R.n = n;
    *T = R;

    return true;
}

bool DeleteChild(PTree *T, TElemType p, int i)
{
    LinkList Lt;
    int index;
    int k, m, n;
    PTree R;
    int parent[MAX_TREE_SIZE];

    // 如果待删除的树为空树则无需继续计算
    if (TreeEmpty(*T))
    {
        return false;
    }

    // i的范围越界（初步判断）
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return false;
    }

    // 获取结点p的第i个孩子索引
    index = CIndex(*T, p, i);

    // 如果待删除结点不存在，则返回错误提示
    if (index == -1)
    {
        return false;
    }

    InitList(&Lt);

    m = 0;
    // 将结点p加入到链表
    ListInsert(Lt, ++m, index);
    T->nodes[index].data = '\0';

    k = (index + 1) % MAX_TREE_SIZE;

    while (k != (T->r + T->n) % MAX_TREE_SIZE)
    {
        // 判断当前结点是否为结点k所在层结点的孩子
        if (LocateElem(Lt, T->nodes[k].parent, Equal))
        {
            ListInsert(Lt, ++m, k);

            T->nodes[k].data = '\0';
        }

        k = (k + 1) % MAX_TREE_SIZE;
    }

    DestroyList(&Lt);

    InitTree(&R);

    R.r = T->r;
    n = 0;

    m = R.r; // 遍历R的游标

    for (k = T->r; k != (T->r + T->n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        if (T->nodes[k].data != '\0')
        {
            // 记录结点k的新位置
            parent[k] = m;

            // 有效元素放到新位置上
            R.nodes[m] = T->nodes[k];

            // 更新父结点位置
            if (R.nodes[m].parent != -1)
            {
                R.nodes[m].parent = parent[R.nodes[m].parent];
            }

            m = (m + 1) % MAX_TREE_SIZE;
            n++;
        }
    }

    R.n = n;
    *T = R;

    return true;
}

bool PreOrderTraverse(PTree T, bool(Visit)(TElemType))
{
    Pos pt[MAX_TREE_SIZE];

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // 计算T中结点的位置信息
    getPos(T, pt);

    PreTraverse(T, pt, T.r, Visit);

    printf("\n");

    return true;
}

bool PostOrderTraverse(PTree T, bool(Visit)(TElemType))
{
    Pos pt[MAX_TREE_SIZE];

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // 计算T中结点的位置信息
    getPos(T, pt);

    PostTraverse(T, pt, T.r, Visit);

    printf("\n");

    return true;
}

bool LevelOrderTraverse(PTree T, bool(Visit)(TElemType))
{
    int i;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // 顺次遍历所有元素
    for (i = T.r; i != (T.r + T.n) % MAX_TREE_SIZE; i = (i + 1) % MAX_TREE_SIZE)
    {
        if (!Visit(T.nodes[i].data))
        {
            return false;
        }
    }

    printf("\n");

    return true;
}

int ReadData(FILE *fp, char *format, ...)
{
    int *i;
    float *f;
    char *ch;
    char *s;
    int n;
    int len;
    int k;
    int tmp;
    va_list ap;
    int count = 0;

    len = strlen(format);
    va_start(ap, format);

    for (k = 1; k <= len; k = k + 2)
    {
        while ((tmp = getc(fp)) != EOF)
        {
            if ((tmp >= 0 && tmp <= 127))
            {
                ungetc(tmp, fp);
                break;
            }
        }

        if (tmp == EOF)
        {
            break;
        }

        if (format[k] == 'c')
        {
            ch = va_arg(ap, char *);
            count += fscanf(fp, "%c", ch);
        }

        if (format[k] == 'd')
        {
            i = va_arg(ap, int *);
            while ((tmp = getc(fp)) != EOF)
            {
                if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+')
                {
                    ungetc(tmp, fp);
                    break;
                }
            }
            if (tmp != EOF)
            {
                count += fscanf(fp, "%d", i);
            }
        }

        if (format[k] == 'f')
        {
            f = va_arg(ap, float *);
            while ((tmp = getc(fp)) != EOF)
            {
                if ((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' || tmp == '.')
                {
                    ungetc(tmp, fp);
                    break;
                }
            }
            if (tmp != EOF)
            {
                count += fscanf(fp, "%f", f);
            }
        }

        if (format[k] == 's')
        {
            s = va_arg(ap, char *);
            n = 0;
            while ((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' '))
            {
            }
            if (!feof(fp))
            {
                ungetc(tmp, fp);
                while ((tmp = getc(fp)) != EOF)
                {
                    if (isprint(tmp) && tmp != ' ')
                    {
                        s[n++] = tmp;
                    }
                    else
                    {
                        ungetc(tmp, fp);
                        break;
                    }
                }
                count++;
            }
            s[n] = '\0';
        }
    }
    va_end(ap);
    return count;
}

static void Create(PTree *T, FILE *fp)
{
    int r;   // 树的根结点的位置（索引）
    int n;   // 记录元素数量
    int cur; // 游标
    TElemType ch;
    LinkQueue Q;
    QElemType e; // 队列元素指示结点的位置
    char s[MAX_CHILD_COUNT + 1];
    int i;

    InitQueue(&Q);

    n = 0;

    // 读取根结点的位置
    if (fp == NULL)
    {
        printf("请输入根结点的位置(0~%d)：", MAX_TREE_SIZE - 1);
        scanf("%d", &r);
        cur = r;

        printf("请输入根结点的值：");
        scanf("%s", s);
        ch = s[0];

        // 树根入队
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;

        while (!QueueEmpty(Q))
        {
            DeQueue(&Q, &e); // 父结点位置出队

            printf("请依次输入 %c 的孩子结点，不存在孩子时输入一个^：", T->nodes[e].data);
            scanf("%s", s);
            for (i = 0; i < strlen(s); i++)
            {
                if (s[i] == '^')
                {
                    break;
                }

                EnQueue(&Q, cur); // 当前结点位置入队
                T->nodes[cur].data = s[i];
                T->nodes[cur].parent = e;
                cur = (cur + 1) % MAX_TREE_SIZE;
                n++;
            }
        }
    }
    else
    {
        // 录入根结点的位置
        ReadData(fp, "%d", &r);
        cur = r;

        // 录入根结点的值
        ReadData(fp, "%s", s);
        ch = s[0];
        printf("录入根结点的值：%c\n", ch);

        // 树根入队
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;

        while (!QueueEmpty(Q))
        {
            ReadData(fp, "%s", s);
            ch = s[0];
            printf("依次录入 %c 结点的孩子：", ch);

            // 录入孩子结点
            ReadData(fp, "%s", s);
            printf("%s\n", s);

            DeQueue(&Q, &e); // 父结点位置出队

            // 遍历孩子
            for (i = 0; i < strlen(s); i++)
            {
                if (s[i] == '^')
                {
                    break;
                }

                EnQueue(&Q, cur); // 当前结点位置入队
                T->nodes[cur].data = s[i];
                T->nodes[cur].parent = e;
                cur = (cur + 1) % MAX_TREE_SIZE;
                n++;
            }
        }
    }

    T->r = r;
    T->n = n;
}

static int EIndex(PTree T, TElemType e)
{
    int i = T.r; // 指向根结点
    int p = -1;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return -1;
    }

    // 在树中查找结点e
    while (i != (T.r + T.n) % MAX_TREE_SIZE)
    {
        if (T.nodes[i].data == e)
        {
            p = i;
            break;
        }

        i = (i + 1) % MAX_TREE_SIZE;
    }

    return p;
}

static int CIndex(PTree T, TElemType e, int i)
{
    int p, k, r, count;

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return -1;
    }

    // i的范围越界
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return -1;
    }

    // 获取结点e的索引
    p = EIndex(T, e);
    // 结点e不存在
    if (p == -1)
    {
        return -1;
    }

    k = (p + 1) % MAX_TREE_SIZE;

    // 查找第一个孩子，用k记录
    while (k != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[k].parent < p)
    {
        k = (k + 1) % MAX_TREE_SIZE;
    }

    // 确保第一个孩子存在
    if (k != (T.r + T.n) % MAX_TREE_SIZE)
    {
        count = 1;
        r = k;

        while (count < i && T.nodes[r].parent == p)
        {
            r = (r + 1) % MAX_TREE_SIZE;
            count++;
        }

        if (count == i)
        {
            return r;
        }
    }

    return -1;
}

static void getPos(PTree T, Pos pt[])
{
    LinkList Lt, Lt_parent, Lt_child;
    int m, n, p, k, s;
    int level;

    memset(pt, 0, MAX_TREE_SIZE * sizeof(Pos));

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        return;
    }

    InitList(&Lt_parent);
    InitList(&Lt_child);

    // 根结点的parent为-1
    ListInsert(Lt_parent, 1, -1);

    level = 1;
    k = T.r;
    m = n = 0;
    s = -1; // 初始化头结点的父结点为-1

    while (k != (T.r + T.n) % MAX_TREE_SIZE)
    {
        // 结点k第一个孩子在树中的索引初始化为-1
        pt[k].firstChild = -1;

        // 结点k最后一个孩子在树中的索引初始化为-1
        pt[k].lastChild = -1;

        // 当前结点k的父结点
        p = T.nodes[k].parent;
        if (p != s)
        {
            s = p; // 追踪父结点的变化
            n = 0; // 父结点改变时，需要重新计数
        }

        // 判断当前结点是否为第level-1层结点的孩子
        if (LocateElem(Lt_parent, p, Equal))
        {
            ListInsert(Lt_child, ++m, k);

            pt[k].row = level;
            pt[k].col = m;
            pt[k].childIndex = ++n;

            // 确保当前结点父结点存在
            if (p != -1)
            {
                // 第一个孩子在树中的索引
                if (pt[p].firstChild == -1)
                {
                    pt[p].firstChild = k;
                }

                // 最后一个孩子在树中的索引
                pt[p].lastChild = k;
            }

            k = (k + 1) % MAX_TREE_SIZE;
        }
        else
        {
            Lt = Lt_parent;
            Lt_parent = Lt_child;
            Lt_child = Lt;
            ClearList(Lt_child);

            level++;
            m = 0;
        }
    }

    DestroyList(&Lt_parent);
    DestroyList(&Lt_child);
}

static bool PreTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType))
{
    int firstChild;
    int rightBrother;

    // 访问当前结点
    if (!Visit(T.nodes[i].data))
    {
        return false;
    }

    firstChild = pt[i].firstChild;

    // 遍历长子（需要先确定长子的身份）
    if (firstChild != -1 && !PreTraverse(T, pt, firstChild, Visit))
    {
        return false;
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // 遍历右兄弟（需要先确定右兄弟的身份）
    if (T.nodes[i].parent == T.nodes[rightBrother].parent && !PreTraverse(T, pt, rightBrother, Visit))
    {
        return false;
    }

    return true;
}

static bool PostTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType))
{
    int firstChild;
    int rightBrother;

    firstChild = pt[i].firstChild;

    // 遍历长子（需要先确定长子的身份）
    if (firstChild != -1 && !PostTraverse(T, pt, firstChild, Visit))
    {
        return false;
    }

    // 访问当前结点
    if (!Visit(T.nodes[i].data))
    {
        return false;
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // 遍历右兄弟（需要先确定右兄弟的身份）
    if (T.nodes[i].parent == T.nodes[rightBrother].parent && !PostTraverse(T, pt, rightBrother, Visit))
    {
        return false;
    }

    return true;
}

static void printPos(PTree T, Pos pt[])
{
    int i;

    for (i = T.r; i != (T.r + T.n) % MAX_TREE_SIZE; i = (i + 1) % MAX_TREE_SIZE)
    {
        printf("%2c ", T.nodes[i].data);
    }
    printf("\n");

    for (i = T.r; i != (T.r + T.n) % MAX_TREE_SIZE; i = (i + 1) % MAX_TREE_SIZE)
    {
        printf("%2d ", pt[i].row);
    }
    printf("\n");

    for (i = T.r; i != (T.r + T.n) % MAX_TREE_SIZE; i = (i + 1) % MAX_TREE_SIZE)
    {
        printf("%2d ", pt[i].col);
    }
    printf("\n");
}

void PrintTree(PTree T)
{
    Pos pt[MAX_TREE_SIZE];

    // 遇到空树则无需继续计算
    if (TreeEmpty(T))
    {
        printf("\n");
        return;
    }

    // 计算T中结点的位置信息
    getPos(T, pt);

    Print(T, pt, T.r);

    printf("\n");

    printf("存储结构：\n");
    PrintFramework(T);
}

static void Print(PTree T, Pos pt[], int i)
{
    int firstChild;
    int rightBrother;
    int k;

    // 访问当前结点
    printf("%c ", T.nodes[i].data);

    firstChild = pt[i].firstChild;

    // 遍历长子（需要先确定长子的身份）
    if (firstChild != -1)
    {
        Print(T, pt, firstChild);
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // 遍历右兄弟（需要先确定右兄弟的身份）
    if (rightBrother != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[i].parent == T.nodes[rightBrother].parent)
    {
        // 访问当前结点的右兄弟前，如果当前结点不是最后一个孩子，则进行一次换行
        if (pt[T.nodes[i].parent].lastChild != i)
        {
            printf("\n");

            for (k = 0; k < pt[rightBrother].row - 1; k++)
            {
                printf(". ");
            }
        }

        Print(T, pt, rightBrother);
    }
}

static void PrintFramework(PTree T)
{
    int k;

    if (T.n == 0)
    {
        printf("\n");
        return;
    }

    printf("+---------+\n");
    printf("|  i e  p |\n");
    printf("+---------+\n");

    for (k = T.r; k != (T.r + T.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        printf("| %2d %c %2d |\n", k, T.nodes[k].data, T.nodes[k].parent);
    }

    printf("+---------+\n");
}
