#include <cstdio>
#include "BiTree.h"

using namespace std;

bool PrintElem(TElemType c) {
    printf("%c", c);
    return true;
}

void menu() {
    puts("0.��ӡ��");
    puts("1.ǰ�����");
    puts("2.�������");
    puts("3.�������");
    puts("4.�������");
    puts("5.�޸Ľڵ�ֵ");
    puts("6.������ڵ�");
    puts("7.���ĳһ�ڵ�ĸ��ڵ�");
    puts("8.������Ҷ���");
    puts("9.��������");
    puts("10.ɾ������");
    puts("11.�����");
    puts("12.�˳�����");
}

int main() {
    SqBiTree T;
    puts("��ʼ���ն�����T...");
    InitBiTree(T);
    puts("���������н���������...");
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
            puts("ǰ��������:");
            PreOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 2:
            puts("����������:");
            InOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 3:
            puts("����������:");
            PostOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 4:
            printf("������ T �����Ϊ��%d \n", BiTreeDepth(T));
            break;
        case 5:
            puts("������Ҫ�޸ĵĽڵ�");
            cin>>e;
            puts("�������޸ĺ������");
            TElemType value;
            cin>>value;
            printf("����� %c �޸�Ϊ %c ��T = \n",e,value);
            Assign(T, e, value);
            PrintTree(T);
            break;
        case 6:
            printf("T�ĸ����Ϊ %c\n", Root(T));
            break;
        case 7:
            puts("������Ҫ���ҵĽڵ�");
            cin>>e;
            printf("��� %c �ĸ��ڵ�Ϊ��%c \n", e, Parent(T, e));
            break;
        case 8:
            puts("������Ҫ���ҵĽڵ�");
            cin>>e;
            printf("��� %c �����ӽ��ֵΪ��%c ���Һ��ӽ��ֵΪ��%c\n", e, LeftChild(T, e), RightChild(T, e));
            break;
        case 9:
            SqBiTree c1;
            puts("������Ҫ�����Ҷ�ӵ�");
            cin>>p1;
            puts("�������� c1 ...");
            InitBiTree(c1);
            CreateBiTree(c1, "NULL");
            PrintTree(c1);
            puts("ѡ�����������or������:");
            puts("0.������\n1.������");
            cin>>pos;
            if(pos==0) {
                printf("������ c1 ����Ϊ������ T �� %c ���������� ...\n", p1);
                InsertChild(T, p1, 0, c1);
                PrintTree(T);
            } else {
                printf("������ c1 ����Ϊ������ T �� %c ���������� ...\n", p1);
                InsertChild(T, p1, 1, c1);
                PrintTree(T);
            }
            break;
        case 10:
            puts("������Ҫɾ����Ҷ�ӵ�");
            cin>>p1;
            puts("ѡ��ɾ��������or������:");
            puts("0.������\n1.������");
            cin>>pos;
            if(pos == 0) {
                printf("ɾ�������� T �� %c ���������� ...\n", p1);
                DeleteChild(T, p1, 0);
                PrintTree(T);
            } else {
                printf("ɾ�������� T �� %c ���������� ...\n", p1);
                DeleteChild(T, p1, 1);
                PrintTree(T);
            }
            break;
        case 11:
            ClearBiTree(T);
            BiTreeEmpty(T) ? printf("T Ϊ�գ�\n") : printf("T ��Ϊ�գ�\n");
            break;
        default:
            break;
        }
    }
}