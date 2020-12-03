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
    puts("1.��ӡ��");
    puts("2.ǰ�����");
    puts("3.�������");
    puts("4.�������");
    puts("5.�޸Ľڵ�ֵ");
    puts("6.������ڵ�");
    puts("7.���ĳһ�ڵ�ĸ��ڵ�");
    puts("8.�������");
    puts("9.��������");
    puts("10.ɾ������");
    puts("11.�����");
    puts("12.�˳�����");
}

int main(int argc, char *argv[])
{
    PTree T;

    printf("�� ��ʼ������ T ...\n");
    InitTree(&T);
    printf("�� ���������д����� T ...\n");
    CreateTree(&T, "TestData_T.txt");
    int n;
    while (true)
    {
        menu();
        puts("���������:");
        scanf("%d", &n);
        if (n == 12)
            return 0;
        TElemType e;
        TElemType p1;
        int pos;
        switch (n)
        {
        case 1:
            puts("���Ľṹ����:");
            PrintTree(T);
            break;
        case 2:
            puts("ǰ��������:");
            PreOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 3:
            puts("����������:");
            PostOrderTraverse(T, PrintElem);
            putchar(10);
            break;
        case 4:
            printf("�� T �����Ϊ��%d \n", TreeDepth(T));
            break;
        case 5:
            puts("������Ҫ�޸ĵĽڵ�");
            cin >> e;
            puts("�������޸ĺ������");
            TElemType value;
            cin >> value;
            printf("����� %c �޸�Ϊ %c ��T = \n", e, value);
            Assign(&T, e, value);
            PrintTree(T);
            break;
        case 6:
            printf("T�ĸ����Ϊ %c\n", Root(T));
            break;
        case 7:
            puts("������Ҫ���ҵĽڵ�");
            cin >> e;
            printf("��� %c �ĸ��ڵ�Ϊ��%c \n", e, Parent(T, e));
            break;
        case 8:
            puts("������Ҫ���ҵĽڵ�");
            cin >> e;
            int i;
            puts("������Ҫ���ҵĵ�i������");
            cin >> i;
            printf("��� %c �ĵ� %d ���ӽ��ֵΪ��%c\n", e, i, Child(T, e, i));
            break;
        case 9:
            PTree c1;
            puts("������Ҫ�����Ҷ�ӵ�");
            cin >> p1;
            puts("�������� c1 ...");
            InitTree(&c1);
            CreateTree(&c1, "TestData_c.txt");
            PrintTree(c1);
            puts("ѡ������pos������:");
            cin >> pos;
            printf("������ c1 ����Ϊ������ T �� %c ���ĵ�pos������ ...\n", p1);
            InsertChild(&T, p1, pos, c1);
            PrintTree(T);
            break;
        case 10:
            puts("������Ҫɾ����Ҷ�ӵ�");
            cin >> p1;
            puts("ѡ������pos������:");
            cin >> pos;
            printf("ɾ�������� T �� %c ���ĵ�pos������ ...\n", p1);
            DeleteChild(&T, p1, pos);
            PrintTree(T);
            break;
        case 11:
            ClearTree(&T);
            TreeEmpty(T) ? printf("T Ϊ�գ�\n") : printf("T ��Ϊ�գ�\n");
            break;
        default:
            break;
        }
    }
    return 0;
}