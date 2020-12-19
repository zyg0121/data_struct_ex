#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

typedef int Boolean;
typedef int ElemType;

// 二叉树的二叉链表结点结构定义
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

/**
 * 递归查找二叉排序树tree中是否存在key
 * 指针front指向tree的双亲，其初始调用值为NULL
 * 若查找成功，则指针p指向该数据元素结点，并返回TRUE；否则指针p指向查找路径上访问的最后一个结点并返回FALSE
 */
Boolean SearchBinarySortTree(BiTree tree, ElemType key, BiTree front, BiTree *p) {
    //查找失败
    if (!tree) {
        *p = front;
        return false;
    }
    //查找成功
    else if (tree->data == key) {
        *p = tree;
        return true;
    }
    else if (tree->data < key) {
        return SearchBinarySortTree(tree->rchild, key, tree, p); // 在该结点的右子树继续查找
    }
    else {
        return SearchBinarySortTree(tree->lchild, key, tree, p); // 在该结点的左子树继续查找
    }
}

/**
 * 当二叉树tree中不存在关键字等于key的数据元素时，插入key并返回TRUE，否则返回FALSE
 */
Boolean InsertBinarySortTree(BiTree *tree, ElemType key) {
    BiTree p, s;
    // 不存在关键字为key的数据元素
    if (!SearchBinarySortTree(*tree, key, NULL, &p)) {
        s = (BiTree)malloc(sizeof(BiTNode));
        if (!s){
            return false;
        }
        s->data = key;
        s->lchild = s->rchild = NULL;
        // p为空则说明二叉查找树为空 
        if (!p) {
            *tree = s; // 作为二叉排序树的根结点
        }
        else if (p->data > key) {
            p->lchild = s; // s结点作为左孩子
        }
        else {
            p->rchild = s; // s结点作为右孩子
        }
        return true;
    }
    return false; // 已经存在关键字为key的数据元素
}

ElemType data[1000+10];

int main() {
    int i;
    Boolean bole;

    BiTree tree = NULL, p;
    puts("Please enter the number of student:");
    int num;
    cin>>num;
    puts("Please enter the id of the student:");
    for(int i=1;i<=num;i++) {
        cin>>data[i];
    }

    for (i = 0; i < num; i++) {
        InsertBinarySortTree(&tree, data[i]);
    }
    puts("Please enter the id who you want to find:");
    int find_num;
    cin>>find_num;
    bole = SearchBinarySortTree(tree, find_num, NULL, &p);
    if (bole == true){
        printf("find successful\n");
    }
    else {
        printf("can not find\n");
    }

    return 0;
}