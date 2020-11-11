#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

//采用链表管理字符串

class Str {
private:
	char str_ch;
public:
	Str() {}
	Str(char ch) {
		str_ch = ch;
	}
	~Str(){}
	char get_ch() {
		return str_ch;
	}
	void set_ch(char ch) {
		str_ch = ch;
	}
};


typedef struct LNode {
	Str data;
	struct LNode *next;
}LNode,*LinkList;


bool InitLinklist(LinkList *L){
	LinkList p;
	p=(LNode *)malloc(sizeof(LNode));
	if(!p)
		exit(-2);
	p->next=NULL;
	*L=p;
	return true;
}

bool GetEmem_L(LinkList L,int i,Str &e) {
	LinkList p = L->next;
	int j = 1;
	while(p && j<i) {
		p =  p->next;
		++j;
	}
	if(!p || j>i) return false;
	e = p->data;
	return true;
}

bool ListInsert_L(LinkList &L,int i,Str e) {
	LinkList p = L;
	int j = 0;
	while(p && j<i-1) {
		p = p->next;
		++j;
	}
	if(!p || j > i-1) return false;
	LinkList s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool ListDelete_L(LinkList &L,int i) {
	LinkList p = L;
	int j = 0;
	while(p->next && j < i-1) {
		p = p->next;
		++j;
	}
	if(!(p->next)||j > i-1) return false;
	LinkList q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

void CreateList_L(LinkList *L,int n) {
	LinkList pi,ptail;
    ptail=*L;
	char ch;
	printf("Please enter the char:\n");
    for(int i = 0;i < n;i++)
    {
        pi=(LNode *)malloc(sizeof(LNode));
        cin>>ch;
		pi->data.set_ch(ch);
        ptail->next=pi;
        ptail=ptail->next;
    }
    pi->next=NULL;
}

void PrintList_L (LinkList *L) {
	puts("The string :");
	LinkList p;
	p =(*L)->next;
	while(p) {
		cout<<p->data.get_ch()<<' ';
		p = p->next;
	}
}


void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.find");
	puts("4.print");
	puts("0.exit");
}


int main() {
    LinkList str;
    puts("Start initialization...");
	InitLinklist(&str);
    puts("please enter the number of the char");
    int k;cin>>k;
    CreateList_L(&str, k);
    int order1;
	menu1();
	cin>>order1;
    while(order1!=0) {
		if (order1 >= 1 && order1 <= 4) {
				if (order1 == 1) {
					int i;
					puts("Please enter the pos do you want insert:");
					cin>>i;
					printf("Please enter the char\n");
                    char e;
                    cin>>e;
					ListInsert_L(str, i, e);
					PrintList_L(&str);
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					ListDelete_L(str, i);
					PrintList_L(&str);
				}
				else if (order1 == 3) {
					int i;
					puts("Please enter the pos do you want to find");
					cin>>i;
                    Str tmp;
                    GetEmem_L(str,i,tmp);
					cout<<"The char is "<<tmp.get_ch();
				}
				else if (order1 == 4) {
					PrintList_L(&str);
				}
				else {
					puts("ERROR input");
				}
        }
		putchar(10);
		puts("-----------------------------");
		puts("Please enter the order:");
		menu1();
		cin>>order1;
    }
}