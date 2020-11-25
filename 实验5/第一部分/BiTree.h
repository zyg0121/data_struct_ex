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

bool InitBiTree(SqBiTree T); //��ʼ�����������
bool DestroyBiTree(SqBiTree T); //���ٶ�����
bool ClearBiTree(SqBiTree T); //��ն�����
bool CreateBiTree(SqBiTree T, char* path); //���ļ���ȡ���ݴ���������
bool BiTreeEmpty(SqBiTree T); //�ж϶������Ƿ�Ϊ��
int BiTreeDepth(SqBiTree T); //�����������ȣ����ٴ����ȣ�
TElemType Value(SqBiTree T, TElemType e); //���ض���������ֵ
bool Assign(SqBiTree T, TElemType e, TElemType value); //������ָ���Ľ�㸳ֵ��
TElemType Root(SqBiTree T); //���ظ��ڵ�
TElemType Parent(SqBiTree T, TElemType e); //���ض������н��e��˫�׽�㡣
TElemType LeftChild(SqBiTree T, TElemType e); //���ض������н��e������ӽ��
TElemType RightChild(SqBiTree T, TElemType e); //���ض������н��e���Ҷ��ӽ��
TElemType LeftSibling(SqBiTree T, TElemType e); //���ض������н��e�����ֵܽ��
TElemType RightSibling(SqBiTree T, TElemType e); //���ض������н��e�����ֵܽ��
bool InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c); //��������
bool DeleteChild(SqBiTree T, TElemType p, int LR); //ɾ������
bool PreOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //�������
bool InOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //�������
bool PostOrderTraverse(SqBiTree T, bool(Visit)(TElemType)); //�������

static void CreateTree(SqBiTree T, int i, FILE* fp); //����������
static int TreeDepth(SqBiTree T, int i); //����������
static int EIndex(SqBiTree T, TElemType e, int i); //���ض��������e�������ţ�i�ǽ��p��������
static void Transfer(SqBiTree T, int i, SqBiTree R, int j); //ժ�¶�����T�е�����i���������Ϊ������R������j
static void Delete(SqBiTree T, int i); // ɾ��������T�е�����i
static bool PreTraverse(SqBiTree T, bool(Visit)(TElemType), int i); // �������
static bool InTraverse(SqBiTree T, bool(Visit)(TElemType), int i); //�������
static bool PostTraverse(SqBiTree T, bool(Visit)(TElemType), int i); // �������
void PrintTree(SqBiTree T); //��Ϊ���۵����һ��������
int ReadData(FILE* fp, char* format, ...); //���ļ���ȡ����

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
        printf("��������������������У����û���ӽ�㣬ʹ��^���棺");
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
        CreateTree(T, 2 * i + 1, fp); // ����������
        CreateTree(T, 2 * i + 2, fp); // ����������
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