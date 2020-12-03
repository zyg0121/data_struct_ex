#include <stdio.h>
#include <iostream>
#include "MuTree.h"
using namespace std;

bool PrintElem(TElemType c)
{
    printf("%c", c);
    return true;
}

void menu()
{
    puts("1.打印树");
    puts("2.前序遍历");
    puts("3.后序遍历");
    puts("4.树的深度");
    puts("5.修改节点值");
    puts("6.输出根节点");
    puts("7.输出某一节点的父节点");
    puts("8.输出儿子");
    puts("9.增加子树");
    puts("10.删除子树");
    puts("11.清空树");
    puts("12.退出程序");
}

int main(int argc, char *argv[])
{
    PTree T;

    printf("█ 初始化空树 T ...\n");
    InitTree(&T);
    printf("█ 按先序序列创建树 T ...\n");
    CreateTree(&T, "TestData_T.txt");
    int n;
    while (true)
    {
        menu();
        puts("请输入操作:");
        scanf("%d", &n);
        if (n == 12)
            return 0;
        TElemType e;
        TElemType p1;
        int pos;
        switch (n)
        {
        case 1:
            puts("树的结构如下:");
            PrintTree(T);
            break;
        case 2:
            puts("前序遍历结果:");
            PreOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 3:
            puts("后序遍历结果:");
            PostOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 4:
            printf("树 T 的深度为：%d \n", TreeDepth(T));
            break;
        case 5:
            puts("请输入要修改的节点");
            cin >> e;
            puts("请输入修改后的名称");
            TElemType value;
            cin >> value;
            printf("将结点 %c 修改为 %c 后，T = \n", e, value);
            Assign(&T, e, value);
            PrintTree(T);
            break;
        case 6:
            printf("T的根结点为 %c\n", Root(T));
            break;
        case 7:
            puts("请输入要查找的节点");
            cin >> e;
            printf("结点 %c 的父节点为：%c \n", e, Parent(T, e));
            break;
        case 8:
            puts("请输入要查找的节点");
            cin >> e;
            int i;
            puts("请输入要查找的第i个儿子");
            cin >> i;
            printf("结点 %c 的第 %d 孩子结点值为：%c\n", e, i, Child(T, e, i));
            break;
        case 9:
            PTree c1;
            puts("请输入要插入的叶子点");
            cin >> p1;
            puts("创建子树 c1 ...");
            InitTree(&c1);
            CreateTree(&c1, "TestData_c.txt");
            PrintTree(c1);
            puts("选择插入第pos个子树:");
            cin >> pos;
            printf("将子树 c1 插入为二叉树 T 中 %c 结点的第pos个子树 ...\n", p1);
            InsertChild(&T, p1, pos, c1);
            PrintTree(T);
            break;
        case 10:
            puts("请输入要删除的叶子点");
            cin >> p1;
            puts("选择插入第pos个子树:");
            cin >> pos;
            printf("删除二叉树 T 中 %c 结点的第pos个子树 ...\n", p1);
            DeleteChild(&T, p1, pos);
            PrintTree(T);
            break;
        case 11:
            ClearTree(&T);
            TreeEmpty(T) ? printf("T 为空！\n") : printf("T 不为空！\n");
            break;
        default:
            break;
        }
    }
    return 0;
}