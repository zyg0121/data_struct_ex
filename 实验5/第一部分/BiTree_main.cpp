#include <cstdio>
#include "BiTree.h"

using namespace std;

bool PrintElem(TElemType c) {
    printf("%c", c);
    return true;
}

void menu() {
    puts("0.打印树");
    puts("1.前序遍历");
    puts("2.中序遍历");
    puts("3.后序遍历");
    puts("4.树的深度");
    puts("5.修改节点值");
    puts("6.输出根节点");
    puts("7.输出某一节点的父节点");
    puts("8.输出左右儿子");
    puts("9.增加子树");
    puts("10.删除子树");
    puts("11.清空树");
    puts("12.退出程序");
}

int main() {
    SqBiTree T;
    puts("初始化空二叉树T...");
    InitBiTree(T);
    puts("按先序序列建立二叉树...");
    CreateBiTree(T, "TestData_Pre.txt");
    int n;
    while(true) {
        menu();
        cin>>n;
        if(n==12) return 0;
        TElemType e;
        TElemType p1;
        int pos;
        switch (n) {
        case 0:
            PrintTree(T);
            break;
        case 1:
            puts("前序遍历结果:");
            PreOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 2:
            puts("中序遍历结果:");
            InOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 3:
            puts("后序遍历结果:");
            PostOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 4:
            printf("二叉树 T 的深度为：%d \n", BiTreeDepth(T));
            break;
        case 5:
            puts("请输入要修改的节点");
            cin>>e;
            puts("请输入修改后的名称");
            TElemType value;
            cin>>value;
            printf("将结点 %c 修改为 %c 后，T = \n",e,value);
            Assign(T, e, value);
            PrintTree(T);
            break;
        case 6:
            printf("T的根结点为 %c\n", Root(T));
            break;
        case 7:
            puts("请输入要查找的节点");
            cin>>e;
            printf("结点 %c 的父节点为：%c \n", e, Parent(T, e));
            break;
        case 8:
            puts("请输入要查找的节点");
            cin>>e;
            printf("结点 %c 的左孩子结点值为：%c ，右孩子结点值为：%c\n", e, LeftChild(T, e), RightChild(T, e));
            break;
        case 9:
            SqBiTree c1;
            puts("请输入要插入的叶子点");
            cin>>p1;
            puts("创建子树 c1 ...");
            InitBiTree(c1);
            CreateBiTree(c1, "NULL");
            PrintTree(c1);
            puts("选择插入左子树or右子树:");
            puts("0.左子树\n1.右子树");
            cin>>pos;
            if(pos==0) {
                printf("将子树 c1 插入为二叉树 T 中 %c 结点的左子树 ...\n", p1);
                InsertChild(T, p1, 0, c1);
                PrintTree(T);
            } else {
                printf("将子树 c1 插入为二叉树 T 中 %c 结点的右子树 ...\n", p1);
                InsertChild(T, p1, 1, c1);
                PrintTree(T);
            }
            break;
        case 10:
            puts("请输入要删除的叶子点");
            cin>>p1;
            puts("选择删除左子树or右子树:");
            puts("0.左子树\n1.右子树");
            cin>>pos;
            if(pos == 0) {
                printf("删除二叉树 T 中 %c 结点的左子树 ...\n", p1);
                DeleteChild(T, p1, 0);
                PrintTree(T);
            } else {
                printf("删除二叉树 T 中 %c 结点的右子树 ...\n", p1);
                DeleteChild(T, p1, 1);
                PrintTree(T);
            }
            break;
        case 11:
            ClearBiTree(T);
            BiTreeEmpty(T) ? printf("T 为空！\n") : printf("T 不为空！\n");
            break;
        default:
            break;
        }
    }
}