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

TR *createTR(char *in, char *pre, int k);   //  ����һ����
void showTR(TR *T);     // չʾһ����   A(B,C(E,F))��������ʽ
TR *destroy(TR *T);     //  ����һ����
void preorder(TR *T);   // ǰ�����
void inorder(TR *T);    // ������� 
void postorder(TR *T);  // �������
void insert(TR *T, char s1, char s2);  // ��dataΪs1�Ľڵ��²���dataΪs2���ӽڵ�
// ��s1���ӽڵ㣬��s2����s1��ĩβ����s1û���ӽڵ㣬��s2��Ϊ�µĽڵ����
TR *delsub(TR *T, char s);      // �ݹ�����ٸ��ڵ�dataΪs������

TR *createTR(char *in, char *pre, int k)
{
    if (k <= 0)
    {
        return NULL;
    }
    else
    {
        TR *node = new TR;         // ����һ���½ڵ�
        node->data = pre[0];      // �½ڵ��dataΪ��ǰ��������Ŀ�ͷ��Ҳ���Ǳ���ݹ鴴�������ĸ��ڵ�
        int i;
        for (i = 0; in[i] != pre[0]; ++ i);     // �����������Ѱ�Ҹ��ڵ㣬i������ڵ�����������е�����
        node->fir = createTR(in, pre + 1, i);	// ���������������֧�ĸ��ڵ�
        node->sib = createTR(in + i + 1, pre + i + 1, k - i  - 1);	// �������������ҷ�֧�ĸ��ڵ�
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
            p2 = p->sib;     // ��Ϊp�ᱻ���٣�������Ҫһ��p2������ָ��Ľڵ��ַ
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
        h1 = height(T->fir) + 1;       // ����T���ӽڵ���ֵܽڵ��һ�㣬������Ҫ��һ
        h2 = height(T->sib);
        return max(h1, h2);
    }
}

void insert(TR *T, char s1, char s2)        // �ݹ�ʵ�ֽڵ�Ĳ���
{
    if (T)
    {
        if (T->data == s1)
        {
            TR *node = new TR;
            node->fir = node->sib = NULL;
            node->data = s2;
            if (T->fir)		// ��ǰ�ڵ����ӽڵ㣬���ҵ����һ���ӽڵ�
            {
                TR *p =  T->fir;
                while (p->sib)
                    p = p->sib;
                p->sib = node;
            }
            else	// ��ǰ�ڵ�û���ӽڵ㣬��ֱ����Ϊ��ǰ�ڵ���ӽڵ�
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
        if (T->fir && T->fir->data == s)	// �����ǰ�ڵ���ӽڵ��������Ҫɾ���Ľڵ㣬����Ҫ�����ӽڵ���ֵܽڵ���������Ȼ�������
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
    char pre[110],in[110];  // Ŀ��������Ӧ�Ķ�����������������������
    puts("                    ************************������ǰ�������********************");
	cin>>pre;
	puts("                    ************************���������������********************");
	cin>>in; 
    TR *header = NULL;
    int length = strlen(pre);
	int n;
	while(1){
	puts("                    *************************1.���������***********************");
	puts("                    *************************2.ǰ�����*************************");
	puts("                    *************************3.�������*************************");
	puts("                    *************************4.�������*************************");
	puts("                    *************************5.��������*************************");
	puts("                    *************************6.ɾ������*************************");
	puts("                    *************************7.���ٶ����***********************");
	puts("                    *************************8.�˳�����************************");
	cout<<"                    *************************�����������***********************"<<endl;
	scanf("%d",&n);
	
	switch(n){
    case 1:
		header = createTR(in, pre, length); // ����һ�Ŷ����
    	cout << "��������Ϊ:" << endl;
    	showTR(header);
    	cout << endl;
    	break;

	case 2:
    	cout << "ǰ�����:" << endl;
    	preorder(header);
    	cout << endl;
    	break;
    	
    case 3:
    	cout << "�������:" << endl;
    	inorder(header);
    	cout << endl;
    	break;

	case 4:
    	cout << "�������:" << endl;
    	postorder(header);
    	cout << endl;
    	break;


	case 5:
    	puts("������Ҫ�����������ǰ�ý���Լ�����");
		char x1,x2;
		cin>>x1;
		cin>>x2; 
		cout << "�������������:" << endl;
 		insert(header,x1,x2);
    	showTR(header);
    	cout << endl;
    	break;

	case 6:
    	puts("������Ҫɾ��������");
        char c;
    	cin>>c;
		cout << "ɾ������Ϊ:" << endl;
		header = delsub(header, c);
    	showTR(header);
    	cout << endl;
    	break;

	case 7: 
    	cout << "������" << endl;
    	destroy(header);
    	break;
    case 8:
    	exit(0);
    default:
    	puts("����Ĳ�����");
    	break;
    }
  }
  return 0;
}
