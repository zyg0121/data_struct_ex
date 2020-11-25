#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cstdarg>
#include <iostream>
using namespace std;

const int Tree_Max_Size = (1<<10)+10;

typedef char TElemType;
typedef TElemType SqBiTree[Tree_Max_Size];

bool InitBiTree(SqBiTree T); //初始化构造二叉树
bool DestroyBiTree(SqBiTree T); //销毁二叉树
bool ClearBiTree(SqBiTree T); //清空二叉树
bool CreateBiTree(SqBiTree T, char* path); //从文件读取数据创建二叉树
bool BiTreeEmpty(SqBiTree T); //判断二叉树是否为空
int BiTreeDepth(SqBiTree T); //求二叉树的深度（多少代祖先）
TElemType Value(SqBiTree T, TElemType e); //返回二叉树结点的值
bool Assign(SqBiTree T, TElemType e, TElemType value); //二叉树指定的结点赋值。
TElemType Root(SqBiTree T); //返回根节点
TElemType Parent(SqBiTree T, TElemType e); //返回二叉树中结点e的双亲结点。
TElemType LeftChild(SqBiTree T, TElemType e); //返回二叉树中结点e的左儿子结点
TElemType RightChild(SqBiTree T, TElemType e); //返回二叉树中结点e的右儿子结点
TElemType LeftSibling(SqBiTree T, TElemType e); //返回二叉树中结点e的左兄弟结点
TElemType RightSibling(SqBiTree T, TElemType e); //返回二叉树中结点e的右兄弟结点
bool InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c); //插入子树
bool DeleteChild(SqBiTree T, TElemType p, int LR); //删除子树
bool PreOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //先序遍历
bool InOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //中序遍历
bool PostOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //后序遍历

static void CreateTree(SqBiTree T, int i, FILE* fp); //创建二叉树
static int TreeDepth(SqBiTree T, int i); //求二叉树深度
static int EIndex(SqBiTree T, TElemType e, int i); //返回二叉树结点e的索引号，i是结点p的索引号
static void Transfer(SqBiTree T, int i, SqBiTree R, int j); //摘下二叉树T中的子树i，将其插入为二叉树R的子树j
static void Delete(SqBiTree T, int i); // 删除二叉树T中的子树i
static bool PreTraverse(SqBiTree T, bool(Visit)(TElemType), int i); // 先序遍历
static bool InTraverse(SqBiTree T, bool(Visit)(TElemType), int i); //中序遍历
static bool PostTraverse(SqBiTree T, bool(Visit)(TElemType), int i); // 后序遍历
void PrintTree(SqBiTree T); //较为美观的输出一个二叉树
int ReadData(FILE* fp, char* format, ...); //从文件读取数据

bool InitBiTree(SqBiTree T) {
    memset(T, '\0', sizeof(SqBiTree));
    return true;
}

bool DestroyBiTree(SqBiTree T) {
    return false;
}

bool ClearBiTree(SqBiTree T) {
    memset(T, '\0', sizeof(SqBiTree));
    return true;
}

bool CreateBiTree(SqBiTree T, char* path) {
    FILE* fp;
    int read_console;
    read_console = path == NULL || strcmp(path, "") == 0;

    if(read_console) {
        printf("请输入二叉树的先序序列，如果没有子结点，使用^代替：");
        CreateTree(T, 0, NULL);
    } else {
        fp = fopen(path, "r");
        if(fp == NULL) {
            return false;
        }
        CreateTree(T, 0, fp);
        fclose(fp);
    }

    return true;
}

bool BiTreeEmpty(SqBiTree T) {
    return T[0] == '\0' ? true : false;
}

int BiTreeDepth(SqBiTree T) {
    return TreeDepth(T, 0);
}

TElemType Value(SqBiTree T, TElemType e) {
    int index;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else {
        return T[index];
    }
}

bool Assign(SqBiTree T, TElemType e, TElemType value) {
    int index;
    if(BiTreeEmpty(T)) {
        return false;
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return false;
    } else {
        T[index] = value;
        return true;
    }
}

TElemType Root(SqBiTree T) {
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    return T[0];
}

TElemType Parent(SqBiTree T, TElemType e) {
    int index;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else if(index == 0) {
        return '\0';
    } else {
        return T[(index - 1) / 2];
    }
}

TElemType LeftChild(SqBiTree T, TElemType e) {
    int index;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else {
        return T[2 * index + 1];
    }
}

TElemType RightChild(SqBiTree T, TElemType e) {
    int index;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else {
        return T[2 * index + 2];
    }
}

TElemType LeftSibling(SqBiTree T, TElemType e) {
    int index, p;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else if(index == 0) {
        return '\0';
    } else {
        p = (index - 1) / 2;
        if(T[2 * p + 2] == e) {
            return T[2 * p + 1];
        } else {
            return '\0';
        }
    }
}

TElemType RightSibling(SqBiTree T, TElemType e) {
    int index, p;
    if(BiTreeEmpty(T)) {
        return '\0';
    }
    index = EIndex(T, e, 0);
    if(index == -1) {
        return '\0';
    } else if(index == 0) {
        return '\0';
    } else {
        p = (index - 1) / 2;
        if(T[2 * p + 1] == e) {
            return T[2 * p + 2];
        } else {
            return '\0';
        }
    }
}


bool InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c) {
    int index;
    if(BiTreeEmpty(c)) {
        return false;
    }
    index = EIndex(T, p, 0);
    if(index == -1) {
        return false;
    }
    if(LR==0) {
        if(T[2*index+1]!='\0') {
            Transfer(T, 2*index+1, c, 2);
        }
        Transfer(c, 0, T, 2*index+1);
    } else {
        if(T[2*index+2]!='\0') {
            Transfer(T, 2*index+2, c, 2);
        }
        Transfer(c, 0, T, 2*index+2);
    }
    return true;
}

bool DeleteChild(SqBiTree T, TElemType p, int LR) {
    int index;
    if(BiTreeEmpty(T)) {
        return false;
    }
    index = EIndex(T, p, 0);
    if(index == -1) {
        return false;
    }
    if(LR == 0) {
        Delete(T, 2 * index + 1);
    } else {
        Delete(T, 2 * index + 2);
    }
    return true;
}

bool PreOrderTraverse(SqBiTree T, bool(Visit)(TElemType)) {
    bool status;
    status = PreTraverse(T, Visit, 0);
    printf("\n");
    return status;
}

bool InOrderTraverse(SqBiTree T, bool(Visit)(TElemType)) {
    bool status;
    status = InTraverse(T, Visit, 0);
    printf("\n");
    return status;
}

bool PostOrderTraverse(SqBiTree T, bool(Visit)(TElemType)) {
    bool status;
    status = PostTraverse(T, Visit, 0);
    printf("\n");
    return status;
}

static void CreateTree(SqBiTree T, int i, FILE* fp) {
    char ch;
    if(fp == NULL) {
        scanf("%c", &ch);
    } else {
        ReadData(fp, "%c", &ch);
    }
    if(ch == '^') {
        T[i] = '\0';
    } else {
        T[i] = ch;
        CreateTree(T, 2 * i + 1, fp); // 创建左子树
        CreateTree(T, 2 * i + 2, fp); // 创建右子树
    }
}

static int TreeDepth(SqBiTree T, int i) {
    int ld, rd;
    if(T[i] == '\0') {
        return 0;
    } else {
        ld = TreeDepth(T, 2 * i + 1);
        rd = TreeDepth(T, 2 * i + 2);
        return (ld >= rd ? ld : rd) + 1;
    }
}

static int EIndex(SqBiTree T, TElemType e, int i) {
    int cl, cr;
    if(i >= Tree_Max_Size) {
        return -1;
    }
    if(e == '\0') {
        return -1;
    }
    if(T[i] == e) {
        return i;
    }
    cl = EIndex(T, e, 2 * i + 1);
    if(cl != -1) {
        return cl;
    }
    cr = EIndex(T, e, 2 * i + 2);
    if(cr != -1) {
        return cr;
    }
    return -1;
}

static void Transfer(SqBiTree T, int i, SqBiTree R, int j) {
    R[j] = T[i];

    if(T[i] != '\0') {
        Transfer(T, 2 * i + 1, R, 2 * j + 1);
        Transfer(T, 2 * i + 2, R, 2 * j + 2);
        T[i] = '\0';
    }
}

static void Delete(SqBiTree T, int i) {
    if(T[i] != '\0') {
        T[i] = '\0';
        Delete(T, 2 * i + 1);
        Delete(T, 2 * i + 2);
    }
}

static bool PreTraverse(SqBiTree T, bool(Visit)(TElemType), int i) {
    if(i >= Tree_Max_Size) {
        return false;
    }

    if(T[i]) {
        if(Visit(T[i])) {
            if(PreTraverse(T, Visit, 2 * i + 1)) {
                if(PreTraverse(T, Visit, 2 * i + 2)) {
                    return true;
                }
            }
        }
        return false;
    } else {
        return true;
    }
}

static bool InTraverse(SqBiTree T, bool(Visit)(TElemType), int i) {
    if(i >= Tree_Max_Size) {
        return false;
    }
    if(T[i]) {
        if(InTraverse(T, Visit, 2 * i + 1)) {
            if(Visit(T[i])) {
                if(InTraverse(T, Visit, 2 * i + 2)) {
                    return true;
                }
            }
        }
        return false;
    } else {
        return true;
    }
}

static bool PostTraverse(SqBiTree T, bool(Visit)(TElemType), int i) {
    if(i >= Tree_Max_Size) {
        return false;
    }
    if(T[i]) {
        if(PostTraverse(T, Visit, 2 * i + 1)) {
            if(PostTraverse(T, Visit, 2 * i + 2)) {
                if(Visit(T[i])) {
                    return true;
                }

            }
        }
        return false;
    } else {
        return true;
    }
}


void PrintTree(SqBiTree T) {
    int level, width;
    int i, j, k, w;
    int begin;
    int distance;
    TElemType** tmp;

    if(BiTreeEmpty(T)) {
        printf("\n");
        return;
    }

    level = BiTreeDepth(T);
    width = (int)pow(2, level)-1;

    tmp = (TElemType**)malloc(level* sizeof(TElemType*));

    for(i = 0; i < level; i++) {
        tmp[i] = (TElemType*)malloc(width* sizeof(TElemType));

        memset(tmp[i], '\0', width);
    }

    for(i = 0; i < level; i++) {
        w = (int) pow(2, i);
        distance = width / w;
        begin    = width / (int) pow(2, i + 1);

        for(k = 0; k < w; k++) {
            j = begin + k * (1 + distance);
            tmp[i][j] = T[(int) pow(2, i) + k - 1];
        }
    }

    for(i = 0; i < level; i++) {
        for(j = 0; j < width; j++) {
            if(tmp[i][j] != '\0') {
                printf("%c", tmp[i][j]);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    putchar(10);
}


int ReadData(FILE* fp, char* format, ...) {
    int* i;
    float* f;
    char* ch;
    char* s;
    int n;
    int len;
    int k;
    int tmp;
    va_list ap;
    int count = 0;

    len = strlen(format);
    va_start(ap, format);

    for(k = 1; k <= len; k = k + 2) {
        while((tmp = getc(fp)) != EOF) {
            if((tmp >= 0 && tmp <= 127)) {
                ungetc(tmp, fp);
                break;
            }
        }

        if(tmp == EOF) {
            break;
        }

        if(format[k] == 'c') {
            ch = va_arg(ap, char*);
            count += fscanf(fp, "%c", ch);
        }

        if(format[k] == 'd') {
            i = va_arg(ap, int*);
            while((tmp = getc(fp)) != EOF) {
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            if(tmp != EOF) {
                count += fscanf(fp, "%d", i);
            }
        }

        if(format[k] == 'f') {
            f = va_arg(ap, float*);
            while((tmp = getc(fp)) != EOF) {
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' || tmp == '.') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            if(tmp != EOF) {
                count += fscanf(fp, "%f", f);
            }
        }

        if(format[k] == 's') {
            s = va_arg(ap, char*);
            n = 0;
            while((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' ')) {
            }
            if(!feof(fp)) {
                ungetc(tmp, fp);
                while((tmp = getc(fp)) != EOF) {
                    if(isprint(tmp) && tmp != ' ') {
                        s[n++] = tmp;
                    } else {
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