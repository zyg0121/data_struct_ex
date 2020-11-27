#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include<stdlib.h>
#define N 100

using namespace std;

typedef struct node
{
    char data;
    struct node *fir, *sib;
}TR;

TR *createTR(char *in, char *pre, int k);   //  创建一棵树
void showTR(TR *T);     // 展示一棵树   A(B,C(E,F))这样的形式
TR *destroy(TR *T);     //  销毁一棵树
void preorder(TR *T);   // 前序遍历
void inorder(TR *T);    // 中序遍历 
void postorder(TR *T);  // 后序遍历
void insert(TR *T, char s1, char s2);  // 在data为s1的节点下插入data为s2的子节点
// 若s1有子节点，则将s2放入s1的末尾；若s1没有子节点，则将s2作为新的节点插入
TR *delsub(TR *T, char s);      // 递归地销毁根节点data为s的子树

TR *createTR(char *in, char *pre, int k)
{
    if (k <= 0)
    {
        return NULL;
    }
    else
    {
        TR *node = new TR;         // 创建一个新节点
        node->data = pre[0];      // 新节点的data为当前先序遍历的开头，也就是本层递归创建的树的根节点
        int i;
        for (i = 0; in[i] != pre[0]; ++ i);     // 在中序遍历中寻找根节点，i代表根节点在中序遍历中的索引
        node->fir = createTR(in, pre + 1, i);	// 创建二叉链的左分支的根节点
        node->sib = createTR(in + i + 1, pre + i + 1, k - i  - 1);	// 创建二叉链的右分支的根节点
        return node;
    }
}

void showTR(TR *T)
{
    if (T)
    {
        cout << T->data;
        if (T->fir)
        {
            cout << "(";
            TR *p = T->fir;
            showTR(p);
            p = p->sib;
            while (p)
            {
            //	count++;
                cout << ",";
                showTR(p);
                p = p->sib;
            }
            cout << ")";
        }
    }
}

TR *destroy(TR *T)
{
    if (!T)
    {
        return NULL;
    }
    else
    {
        TR *p = T->fir, *p2;
        while(p)
        {
            p2 = p->sib;     // 因为p会被销毁，所以需要一个p2来保存指向的节点地址
            destroy(p);
            p = p2;
        }
        delete T;
        return NULL;
    }
}

void preorder(TR *T)
{
    if (T)
    {
        cout << T->data << " ";
        preorder(T->fir);
        preorder(T->sib);
    }
}

void inorder(TR *T) {
	if(T) {
		inorder(T->fir);
		inorder(T->sib);
		cout<<T->data<<" ";
	}
}

void postorder(TR *T)
{
    if (T)
    {
        postorder(T->fir);
        cout << T->data << " ";
        postorder(T->sib);
    }
}

int height(TR *T)
{
    if (!T)
    {
        return 0;
    }
    else
    {
        int h1, h2;
        h1 = height(T->fir) + 1;       // 由于T的子节点比兄弟节点低一层，所以需要加一
        h2 = height(T->sib);
        return max(h1, h2);
    }
}

void insert(TR *T, char s1, char s2)        // 递归实现节点的插入
{
    if (T)
    {
        if (T->data == s1)
        {
            TR *node = new TR;
            node->fir = node->sib = NULL;
            node->data = s2;
            if (T->fir)		// 当前节点有子节点，则找到最后一个子节点
            {
                TR *p =  T->fir;
                while (p->sib)
                    p = p->sib;
                p->sib = node;
            }
            else	// 当前节点没有子节点，则直接作为当前节点的子节点
            {
                T->fir = node;
            }
        }
        else
        {
            insert(T->fir, s1, s2);
            insert(T->sib, s1, s2);
        }
    }
}

TR *delsub(TR *T, char s)
{
    if (!T)
    {
        return NULL;
    }
    else if (T->data == s)
    {
        return destroy(T);
    }
    else
    {
        if (T->fir && T->fir->data == s)	// 如果当前节点的子节点就是我们要删除的节点，则需要把其子节点的兄弟节点做处理（当然，如果）
            T->fir = T->fir->sib;
        delsub(T->fir, s);

        if (T->sib && T->sib->data == s)
            T->sib = T->sib->sib;
        delsub(T->sib, s);
        return T;
    }
}

int main()
{
    char pre[110],in[110];  // 目标多叉树对应的二叉链的先序遍历和中序遍历
    puts("                    ************************请输入前序遍历：********************");
	cin>>pre;
	puts("                    ************************请输入中序遍历：********************");
	cin>>in; 
    TR *header = NULL;
    int length = strlen(pre);
	int n;
	while(1){
	puts("                    *************************1.创建多叉树***********************");
	puts("                    *************************2.前序遍历*************************");
	puts("                    *************************3.后序遍历*************************");
	puts("                    *************************4.中序遍历*************************");
	puts("                    *************************5.插入子树*************************");
	puts("                    *************************6.删除子树*************************");
	puts("                    *************************7.销毁多叉树***********************");
	puts("                    *************************8.退出程序************************");
	cout<<"                    *************************请输入操作数***********************"<<endl;
	scanf("%d",&n);
	
	switch(n){
    case 1:
		header = createTR(in, pre, length); // 创建一颗多叉树
    	cout << "创建的树为:" << endl;
    	showTR(header);
    	cout << endl;
    	break;

	case 2:
    	cout << "前序遍历:" << endl;
    	preorder(header);
    	cout << endl;
    	break;
    	
    case 3:
    	cout << "后序遍历:" << endl;
    	inorder(header);
    	cout << endl;
    	break;

	case 4:
    	cout << "中序遍历:" << endl;
    	postorder(header);
    	cout << endl;
    	break;


	case 5:
    	puts("请输入要插入的子树的前置结点以及内容");
		char x1,x2;
		cin>>x1;
		cin>>x2; 
		cout << "插入子树后的树:" << endl;
 		insert(header,x1,x2);
    	showTR(header);
    	cout << endl;
    	break;

	case 6:
    	puts("请输入要删除的子树");
        char c;
    	cin>>c;
		cout << "删除后，树为:" << endl;
		header = delsub(header, c);
    	showTR(header);
    	cout << endl;
    	break;

	case 7: 
    	cout << "销毁树" << endl;
    	destroy(header);
    	break;
    case 8:
    	exit(0);
    default:
    	puts("错误的操作数");
    	break;
    }
  }
  return 0;
}
