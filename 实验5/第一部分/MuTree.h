#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdarg>
#include <cctype>
#include "LinkList.h"
#include "LinkQueue.h"

/* ����������� */
const int MAX_TREE_SIZE = 1024;

/* ����������ĺ������� */
const int MAX_CHILD_COUNT = 8;

/* ����Ԫ�����Ͷ��壬���������Ԫ������Ϊchar */
typedef char TElemType;

typedef struct PTNode
{
    TElemType data;
    int parent; // ˫��λ����
} PTNode;

/*
 * �����Ͷ���
 */
typedef struct
{
    PTNode nodes[MAX_TREE_SIZE]; // �洢���н��
    int r;                       // ����λ��(����)
    int n;                       // ���Ľ����
} PTree;

/* ����ĳ��������Ϣ */
typedef struct
{
    int row;        // ��ǰ�����������
    int col;        // ��ǰ�����������
    int childIndex; // ��ǰ����ǵڼ�������
    int firstChild; // ��ǰ���ĵ�һ�����������е�����
    int lastChild;  // ��ǰ�������һ�����������е�����
} Pos;
/*
 * ��ʼ��
 *
 * ���������
 */
bool InitTree(PTree *T);
/*
 * ����
 *
 * �ͷ�����ռ�ڴ档
 */
bool DestroyTree(PTree *T);
/*
 * �ÿ�
 *
 * �������е����ݣ�ʹ���Ϊ������
 */
bool ClearTree(PTree *T);
/*
 * ����
 *
 * ����Ԥ��Ķ�������������
 * ����Լ��ʹ�á��������С�����������
 */
bool CreateTree(PTree *T, char *path);
/*
 * �п�
 *
 * �ж����Ƿ�Ϊ������
 */
bool TreeEmpty(PTree T);
/*
 * ����
 *
 * ����������ȣ���������
 */
int TreeDepth(PTree T);
/*
 * ȡֵ
 *
 * ��������ָ������ֵ��
 */
TElemType Value(PTree T, TElemType e);
/*
 * ��ֵ
 *
 * Ϊ��ָ���Ľ�㸳ֵ��
 */
bool Assign(PTree *T, TElemType e, TElemType value);
/*
 * ��
 *
 * �������ĸ���㡣
 */
TElemType Root(PTree T);
/*
 * ˫��
 *
 * �������н��e��˫�׽�㡣
 */
TElemType Parent(PTree T, TElemType e);
/*
 * ��������
 *
 * ������T�н��e�ĺ���������
 */
int ChildCount(PTree T, TElemType e);
/*
 * ����
 *
 * �������н��e�ĵ�i�����ӡ�
 */
TElemType Child(PTree T, TElemType e, int i);
/*
 * ���ֵ�
 *
 * �������н��e�����ֵܽ�㡣
 *
 *��ע��
 * �������Ľ����ܻ����������ӣ�
 * �����������ֵ���ָ��߽��ڸý����ֵܡ�
 */
TElemType LeftSibling(PTree T, TElemType e);
/*
 * ���ֵ�
 *
 * �������н��e�����ֵܽ�㡣
 *
 *��ע��
 * �������Ľ����ܻ����������ӣ�
 * �����������ֵ���ָ�ұ߽��ڸý����ֵܡ�
 */
TElemType RightSibling(PTree T, TElemType e);
/*
 * ����
 *
 * ����c����Ϊ��T��p���ĵ�i�����ӡ�
 */
bool InsertChild(PTree *T, TElemType p, int i, PTree c);
/*
 * ɾ��
 *
 * ɾ����T��p���ĵ�i�����ӡ�
 */
bool DeleteChild(PTree *T, TElemType p, int i);
/*
 * �������
 */
bool PreOrderTraverse(PTree T, bool(Visit)(TElemType));
/*
 * �������
 */
bool PostOrderTraverse(PTree T, bool(Visit)(TElemType));
/*
 * �������
 */
bool LevelOrderTraverse(PTree T, bool(Visit)(TElemType));
// ���������ڲ�����
static void Create(PTree *T, FILE *fp);
// ���������e����������������ڣ�����-1
static int EIndex(PTree T, TElemType e);
// ���������e�ĵ�i��������������������ڣ�����-1
static int CIndex(PTree T, TElemType e, int i);
// ��ȡ��T�Ľ����Ϣ�����������Щ��Ϣ�������Pos���͵Ķ���
static void getPos(PTree T, Pos pt[]);
// ����������ڲ�ʵ��
static bool PreTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType));
// ����������ڲ�ʵ��
static bool PostTraverse(PTree T, Pos pt[], int i, bool(Visit)(TElemType));
// ���pos��Ϣ
static void printPos(PTree T, Pos pt[]);
// ��ͼ�λ���ʽ�����ǰ�ṹ
void PrintTree(PTree T);
// ͼ�λ������ǰ�ṹ�ڲ�ʵ��
static void Print(PTree T, Pos pt[], int i);
// ͼ�λ�����������нṹ
static void PrintFramework(PTree T);
//��ȡ�ļ���Ϣ
int ReadData(FILE *fp, char *format, ...);

bool InitTree(PTree *T)
{
    if (T == NULL)
    {
        return false;
    }

    T->n = 0;

    // ������������
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

    // ��Ԫ���������㼴��
    T->n = 0;

    // ������������
    memset(T->nodes, 0, sizeof(T->nodes));

    return true;
}

bool CreateTree(PTree *T, char *path)
{
    FILE *fp;
    int readFromConsole; // �Ƿ�ӿ���̨��ȡ����

    // ���û���ļ�·����Ϣ����ӿ���̨��ȡ����
    readFromConsole = path == NULL || strcmp(path, "") == 0;

    if (readFromConsole)
    {
        printf("����������Ԫ����Ϣ�����ڿս�㣬ʹ��^����...\n");
        Create(T, NULL);
    }
    else
    {
        // ���ļ���׼����ȡ��������
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return 0;
    }

    /*
     * ��k��ʼ��Ϊ���һ������λ��
     * �������Ľ�㰴����洢�������洢�Ľ��ض�λ������
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // ��ȡ���e������
    p = EIndex(T, e);

    // ���û���ҵ�Ԫ��e
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

    // ���������������������
    if (TreeEmpty(*T))
    {
        return false;
    }

    // ��ȡ���e������
    p = EIndex(*T, e);

    // ���û���ҵ�Ԫ��e
    if (p == -1)
    {
        return false;
    }
    else
    {
        // ���и�ֵ
        T->nodes[p].data = value;
        return true;
    }
}

TElemType Root(PTree T)
{
    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    return T.nodes[T.r].data;
}

TElemType Parent(PTree T, TElemType e)
{
    int p, parent;

    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // ��ȡ���e������
    p = EIndex(T, e);

    // ���û���ҵ�Ԫ��e
    if (p == -1)
    {
        return '\0';
    }
    else
    {
        parent = T.nodes[p].parent;

        // �������˫��
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return -1;
    }

    // ��ȡ���e������
    p = EIndex(T, e);
    // ���e������
    if (p == -1)
    {
        return -1;
    }

    // ���ҵ�һ������
    for (k = (p + 1) % MAX_TREE_SIZE; k != (T.r + T.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        if (T.nodes[k].parent == p)
        {
            break;
        }
    }

    count = 0;

    // ͳ�ƽ��e�ĺ�������
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // i�ķ�ΧԽ��
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return '\0';
    }

    // ��ȡ���e�ĵ�i����������
    p = CIndex(T, e, i);
    // ���e��i�����Ӳ�����
    if (p == -1)
    {
        return '\0';
    }

    return T.nodes[p].data;
}

TElemType LeftSibling(PTree T, TElemType e)
{
    int p, ls;

    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // ��ȡ���e������
    p = EIndex(T, e);
    // ���e������
    if (p == -1)
    {
        return '\0';
    }

    // ����������ֵ�
    ls = (p - 1 + MAX_TREE_SIZE) % MAX_TREE_SIZE;

    // ����ý����Ч��������e��˫����ͬ��˵�������ֵ�
    if (ls != p && T.nodes[ls].data != '\0' && T.nodes[ls].parent == T.nodes[p].parent)
    {
        return T.nodes[ls].data;
    }

    return '\0';
}

TElemType RightSibling(PTree T, TElemType e)
{
    int p, rs;

    // ���������������������
    if (TreeEmpty(T))
    {
        return '\0';
    }

    // ��ȡ���e������
    p = EIndex(T, e);
    // ���e������
    if (p == -1)
    {
        return '\0';
    }

    // ����������ֵ�
    rs = (p + 1) % MAX_TREE_SIZE;

    // ����ý����Ч��������e��˫����ͬ��˵�������ֵ�
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

    // �����Ϊ�����������������
    if (TreeEmpty(*T) || TreeEmpty(c))
    {
        return false;
    }

    // i�ķ�Χ����С
    if (i < 1)
    {
        return false;
    }

    // ��ȡ���p������
    pIndex = EIndex(*T, p);

    // ���p��㲻���ڣ��򷵻ش�����ʾ
    if (pIndex == -1)
    {
        return false;
    }

    // ����T�н���λ����Ϣ
    getPos(*T, pt);

    // ���p���һ�����ӵ�����
    lastChild = pt[pIndex].lastChild;

    // i�ķ�Χ����
    if (lastChild != -1 && i > pt[lastChild].childIndex + 1)
    {
        return false;
    }

    if (i == 1)
    {
        // ���p�����ǵ�һ������
        if (pt[pIndex].childIndex == 1)
        {
            bound = -1;
        }
        else
        {
            // ��p�����ֵ����������
            for (k = (pIndex - 1) % MAX_TREE_SIZE; pt[k].lastChild == -1 && pt[k].childIndex != 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // �����ұ߽�ĸ���������
            }

            // �Ѿ��������ò��һ����㣬���ý����Ȼû�к���
            if (pt[k].lastChild == -1)
            {
                bound = -1;
            }
            else
            {
                bound = pt[k].lastChild; // k������һ�����ӵ�����
            }
        }
    }
    else
    {
        // ���pû�к���
        if (lastChild == -1)
        {
            return false;
        }
        else
        {
            for (k = pt[pIndex].lastChild; pt[k].childIndex != i - 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // ���Ҳ���λ�õ�ǰһ�����ӵ�����
            }
            bound = k;
        }
    }

    level = pt[pIndex].row + 1; // ����������ĸ�������ڵ���

    // ����c�н���λ����Ϣ
    getPos(c, pc);
    // �����²�������и�Ԫ�ص�����
    for (k = c.r; k != (c.r + c.n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        pc[k].row += level - 1;
    }

    // tCurָ���level�еĵ�һ�����
    for (tCur = pIndex; tCur != (T->r + T->n) % MAX_TREE_SIZE; tCur = (tCur + 1) % MAX_TREE_SIZE)
    {
        if (pt[tCur].row == level)
        {
            break;
        }
    }

    // cCurָ����c�еĸ���㣬�ø����ҲӦ�����뵽��T�е�level��
    cCur = c.r;

    while (tCur != (T->r + T->n) % MAX_TREE_SIZE && cCur != (c.r + c.n) % MAX_TREE_SIZE)
    {
        // ������T�ҽ��ǰ�벿��
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

        // ��c���뵽T���м�
        while (cCur != (c.r + c.n) % MAX_TREE_SIZE && pc[cCur].row == level)
        {
            // �ı���

            pc[cCur].col += m;
            n++;

            cCur++;
        }

        // ����T�ĺ�벿��
        while (tCur != (T->r + T->n) % MAX_TREE_SIZE && pt[tCur].row == level)
        {

            pt[tCur].col += n;

            tCur++;
        }

        // ������һ��ı߽�
        if (bound != -1)
        {
            // ��bound���������
            for (k = bound; pt[k].lastChild == -1 && pt[k].childIndex != 1; k = (k - 1) % MAX_TREE_SIZE)
            {
                // �����ұ߽�ĸ���������
            }

            // �Ѿ��������ò��һ����㣬���ý����Ȼû�к���
            if (pt[k].lastChild == -1)
            {
                bound = -1;
            }
            else
            {
                bound = pt[k].lastChild; // k������һ�����ӵ�����
            }
        }

        level++;
    }

    // ����pos��Ϣ
    //    printPos(*T, pt);
    //    printPos(c, pc);

    InitTree(&R);

    R.r = T->r;
    n = 0;

    x = T->r; // ����T���α�
    y = c.r;  // ����c���α�
    z = R.r;  // ����R���α�

    while (x != (T->r + T->n) % MAX_TREE_SIZE && y != (c.r + c.n) % MAX_TREE_SIZE)
    {
        if (pt[x].row < pc[y].row || (pt[x].row == pc[y].row && pt[x].col < pc[y].col))
        {

            // ��¼���x����λ��
            tParent[x] = z;

            // ��ЧԪ�طŵ���λ����
            R.nodes[z] = T->nodes[x];

            if (R.nodes[z].parent != -1)
            {
                // ���¸����λ��
                R.nodes[z].parent = tParent[R.nodes[z].parent];
            }

            x = (x + 1) % MAX_TREE_SIZE;
        }
        else if (pt[x].row > pc[y].row || (pt[x].row == pc[y].row && pt[x].col > pc[y].col))
        {
            // ��¼���y����λ��
            cParent[y] = z;

            // ��ЧԪ�طŵ���λ����
            R.nodes[z] = c.nodes[y];

            if (R.nodes[z].parent != -1)
            {
                // ���¸����λ��
                R.nodes[z].parent = cParent[R.nodes[z].parent];
            }
            else
            {
                // ������������һ�𣬼���c�ĸ����ĸ����Ϊp
                R.nodes[z].parent = tParent[pIndex];
            }

            y = (y + 1) % MAX_TREE_SIZE;
        }

        z = (z + 1) % MAX_TREE_SIZE;
        n++;
    }

    while (x != (T->r + T->n) % MAX_TREE_SIZE)
    {
        // ��¼���k����λ��
        tParent[x] = z;

        // ��ЧԪ�طŵ���λ����
        R.nodes[z] = T->nodes[x];

        if (R.nodes[z].parent != -1)
        {
            // ���¸����λ��
            R.nodes[z].parent = tParent[R.nodes[z].parent];
        }

        x = (x + 1) % MAX_TREE_SIZE;
        z = (z + 1) % MAX_TREE_SIZE;
        n++;
    }

    while (y != (c.r + c.n) % MAX_TREE_SIZE)
    {
        // ��¼���k����λ��
        cParent[y] = z;

        // ��ЧԪ�طŵ���λ����
        R.nodes[z] = c.nodes[y];

        if (R.nodes[z].parent != -1)
        {
            // ���¸����λ��
            R.nodes[z].parent = cParent[R.nodes[z].parent];
        }
        else
        {
            // ������������һ�𣬼���c�ĸ����ĸ����Ϊp
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

    // �����ɾ������Ϊ�����������������
    if (TreeEmpty(*T))
    {
        return false;
    }

    // i�ķ�ΧԽ�磨�����жϣ�
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return false;
    }

    // ��ȡ���p�ĵ�i����������
    index = CIndex(*T, p, i);

    // �����ɾ����㲻���ڣ��򷵻ش�����ʾ
    if (index == -1)
    {
        return false;
    }

    InitList(&Lt);

    m = 0;
    // �����p���뵽����
    ListInsert(Lt, ++m, index);
    T->nodes[index].data = '\0';

    k = (index + 1) % MAX_TREE_SIZE;

    while (k != (T->r + T->n) % MAX_TREE_SIZE)
    {
        // �жϵ�ǰ����Ƿ�Ϊ���k���ڲ���ĺ���
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

    m = R.r; // ����R���α�

    for (k = T->r; k != (T->r + T->n) % MAX_TREE_SIZE; k = (k + 1) % MAX_TREE_SIZE)
    {
        if (T->nodes[k].data != '\0')
        {
            // ��¼���k����λ��
            parent[k] = m;

            // ��ЧԪ�طŵ���λ����
            R.nodes[m] = T->nodes[k];

            // ���¸����λ��
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

    // ���������������������
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // ����T�н���λ����Ϣ
    getPos(T, pt);

    PreTraverse(T, pt, T.r, Visit);

    printf("\n");

    return true;
}

bool PostOrderTraverse(PTree T, bool(Visit)(TElemType))
{
    Pos pt[MAX_TREE_SIZE];

    // ���������������������
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // ����T�н���λ����Ϣ
    getPos(T, pt);

    PostTraverse(T, pt, T.r, Visit);

    printf("\n");

    return true;
}

bool LevelOrderTraverse(PTree T, bool(Visit)(TElemType))
{
    int i;

    // ���������������������
    if (TreeEmpty(T))
    {
        printf("\n");
        return false;
    }

    // ˳�α�������Ԫ��
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
    int r;   // ���ĸ�����λ�ã�������
    int n;   // ��¼Ԫ������
    int cur; // �α�
    TElemType ch;
    LinkQueue Q;
    QElemType e; // ����Ԫ��ָʾ����λ��
    char s[MAX_CHILD_COUNT + 1];
    int i;

    InitQueue(&Q);

    n = 0;

    // ��ȡ������λ��
    if (fp == NULL)
    {
        printf("�����������λ��(0~%d)��", MAX_TREE_SIZE - 1);
        scanf("%d", &r);
        cur = r;

        printf("�����������ֵ��");
        scanf("%s", s);
        ch = s[0];

        // �������
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;

        while (!QueueEmpty(Q))
        {
            DeQueue(&Q, &e); // �����λ�ó���

            printf("���������� %c �ĺ��ӽ�㣬�����ں���ʱ����һ��^��", T->nodes[e].data);
            scanf("%s", s);
            for (i = 0; i < strlen(s); i++)
            {
                if (s[i] == '^')
                {
                    break;
                }

                EnQueue(&Q, cur); // ��ǰ���λ�����
                T->nodes[cur].data = s[i];
                T->nodes[cur].parent = e;
                cur = (cur + 1) % MAX_TREE_SIZE;
                n++;
            }
        }
    }
    else
    {
        // ¼�������λ��
        ReadData(fp, "%d", &r);
        cur = r;

        // ¼�������ֵ
        ReadData(fp, "%s", s);
        ch = s[0];
        printf("¼�������ֵ��%c\n", ch);

        // �������
        EnQueue(&Q, cur);
        T->nodes[cur].data = ch;
        T->nodes[cur].parent = -1;
        cur = (cur + 1) % MAX_TREE_SIZE;
        n++;

        while (!QueueEmpty(Q))
        {
            ReadData(fp, "%s", s);
            ch = s[0];
            printf("����¼�� %c ���ĺ��ӣ�", ch);

            // ¼�뺢�ӽ��
            ReadData(fp, "%s", s);
            printf("%s\n", s);

            DeQueue(&Q, &e); // �����λ�ó���

            // ��������
            for (i = 0; i < strlen(s); i++)
            {
                if (s[i] == '^')
                {
                    break;
                }

                EnQueue(&Q, cur); // ��ǰ���λ�����
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
    int i = T.r; // ָ������
    int p = -1;

    // ���������������������
    if (TreeEmpty(T))
    {
        return -1;
    }

    // �����в��ҽ��e
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return -1;
    }

    // i�ķ�ΧԽ��
    if (i < 1 || i > MAX_CHILD_COUNT)
    {
        return -1;
    }

    // ��ȡ���e������
    p = EIndex(T, e);
    // ���e������
    if (p == -1)
    {
        return -1;
    }

    k = (p + 1) % MAX_TREE_SIZE;

    // ���ҵ�һ�����ӣ���k��¼
    while (k != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[k].parent < p)
    {
        k = (k + 1) % MAX_TREE_SIZE;
    }

    // ȷ����һ�����Ӵ���
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

    // ���������������������
    if (TreeEmpty(T))
    {
        return;
    }

    InitList(&Lt_parent);
    InitList(&Lt_child);

    // ������parentΪ-1
    ListInsert(Lt_parent, 1, -1);

    level = 1;
    k = T.r;
    m = n = 0;
    s = -1; // ��ʼ��ͷ���ĸ����Ϊ-1

    while (k != (T.r + T.n) % MAX_TREE_SIZE)
    {
        // ���k��һ�����������е�������ʼ��Ϊ-1
        pt[k].firstChild = -1;

        // ���k���һ�����������е�������ʼ��Ϊ-1
        pt[k].lastChild = -1;

        // ��ǰ���k�ĸ����
        p = T.nodes[k].parent;
        if (p != s)
        {
            s = p; // ׷�ٸ����ı仯
            n = 0; // �����ı�ʱ����Ҫ���¼���
        }

        // �жϵ�ǰ����Ƿ�Ϊ��level-1����ĺ���
        if (LocateElem(Lt_parent, p, Equal))
        {
            ListInsert(Lt_child, ++m, k);

            pt[k].row = level;
            pt[k].col = m;
            pt[k].childIndex = ++n;

            // ȷ����ǰ��㸸������
            if (p != -1)
            {
                // ��һ�����������е�����
                if (pt[p].firstChild == -1)
                {
                    pt[p].firstChild = k;
                }

                // ���һ�����������е�����
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

    // ���ʵ�ǰ���
    if (!Visit(T.nodes[i].data))
    {
        return false;
    }

    firstChild = pt[i].firstChild;

    // �������ӣ���Ҫ��ȷ�����ӵ���ݣ�
    if (firstChild != -1 && !PreTraverse(T, pt, firstChild, Visit))
    {
        return false;
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // �������ֵܣ���Ҫ��ȷ�����ֵܵ���ݣ�
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

    // �������ӣ���Ҫ��ȷ�����ӵ���ݣ�
    if (firstChild != -1 && !PostTraverse(T, pt, firstChild, Visit))
    {
        return false;
    }

    // ���ʵ�ǰ���
    if (!Visit(T.nodes[i].data))
    {
        return false;
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // �������ֵܣ���Ҫ��ȷ�����ֵܵ���ݣ�
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

    // ���������������������
    if (TreeEmpty(T))
    {
        printf("\n");
        return;
    }

    // ����T�н���λ����Ϣ
    getPos(T, pt);

    Print(T, pt, T.r);

    printf("\n");

    printf("�洢�ṹ��\n");
    PrintFramework(T);
}

static void Print(PTree T, Pos pt[], int i)
{
    int firstChild;
    int rightBrother;
    int k;

    // ���ʵ�ǰ���
    printf("%c ", T.nodes[i].data);

    firstChild = pt[i].firstChild;

    // �������ӣ���Ҫ��ȷ�����ӵ���ݣ�
    if (firstChild != -1)
    {
        Print(T, pt, firstChild);
    }

    rightBrother = (i + 1) % MAX_TREE_SIZE;

    // �������ֵܣ���Ҫ��ȷ�����ֵܵ���ݣ�
    if (rightBrother != (T.r + T.n) % MAX_TREE_SIZE && T.nodes[i].parent == T.nodes[rightBrother].parent)
    {
        // ���ʵ�ǰ�������ֵ�ǰ�������ǰ��㲻�����һ�����ӣ������һ�λ���
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
