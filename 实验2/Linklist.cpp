#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class stu_dorm {
private:
	int dorm_num;//renshu
	double dorm_size;//mianji
	int dorm_people;//reshu
	int dorm_condition;//tiaojian
public:
	stu_dorm() {}
	stu_dorm(int num, double size, int people, int condition) {
		dorm_condition = condition;
		dorm_num = num;
		dorm_people = people;
		dorm_size = size;
	}
	~stu_dorm(){}
	int get_num() {
		return dorm_num;
	}
	double get_size() {
		return dorm_size;
	}
	int get_people() {
		return dorm_people;
	}
	int get_condition() {
		return dorm_condition;
	}

	void set_num(int num) {
		dorm_num = num;
	}
	void set_condition(int condition) {
		dorm_condition = condition;
	}
	void set_pople(int people) {
		dorm_people = people;
	}
	void set_size(double size) {
		dorm_size = size;
	}

};

typedef struct LNode {
	stu_dorm data;
	struct LNode *next;
}LNode,*LinkList;

bool GetEmem_L(LinkList L,int i,stu_dorm &e) {
	LNode *p = L->next;
	int j = 1;
	while(p && j<i) {
		p =  p->next;
		++j;
	}
	if(!p || j>i) return false;
	e = p->data;
	return true;
}

bool ListInsert_L(LinkList &L,int i,stu_dorm e) {
	LNode *p = L;
	int j = 0;
	while(p && j<i-1) {
		p = p->next;
		++j;
	}
	if(!p || j > i-1) return false;
	LNode *s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

bool ListDelete_L(LinkList &L,int i,stu_dorm &e) {
	LNode *p = L;
	int j = 0;
	while(p->next && j < i-1) {
		p = p->next;
		++j;
	}
	if(!(p->next)||j > i-1) return false;
	LNode *q = p->next;
	p->next = q->next;
	e = q->data;
	free(q);
	return true;
}

void CreateList_L(LinkList &L,int n) {
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	int num, people;
	double size;
	int condition;
	for(int i = n;i > 0;i--) {
		LNode *p = (LinkList) malloc(sizeof(LNode));
		cin>>num;
		cin>>size;
		cin>>people;
		cin>>condition;
		L->data.set_condition(condition);
		L->data.set_num(num);
		L->data.set_pople(people);
		L->data.set_size(size);
		p->next = L->next;
		L->next = p;
	}
}

void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc) {
	LNode *pa = La->next;
	LNode *pb = Lb->next;
	LNode *pc;
	Lc = pc = La;
	while(pa) {
		pc->next = pa; pc = pa; pa = pa->next;
	}
	while(pb) {
		pc->next = pb; pc = pb; pb = pb->next;
	}
	free(Lb);
}

void PrintList_L(LinkList &L) {
	LNode *p = L;
	printf("SqList(num,size,people,condition):\n");
	while(p){
		cout<<p->data.get_num()<<' '<<p->data.get_size()<<' '<<p->data.get_people()<<' '<<p->data.get_condition()<<endl;
		p = p->next;
	}
}


void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.find");
	puts("4.print");
	puts("5.Merge");
	puts("0.exit");
}

void menu2() {
	puts("1.first_floor");
	puts("2.second_floor");
}

int main() {
	LinkList first_floor;
	LinkList second_floor;
	puts("Plese enter the first floor dorm element:");
	int k;
	puts("please enter the number of the rooms");
	cin>>k;
	CreateList_L(first_floor, k);
	puts("Plese enter the second floor dorm element:");
	puts("please enter the number of the rooms");
	cin>>k;
	CreateList_L(second_floor, k);
	
	puts("Please enter the order:");
	int order1,order2;
	menu1();
	cin>>order1;
	while(order1!=0) {
		if (order1 >= 1 && order1 <= 4) {
			puts("Please enter the floor");
			cin>>order2;
			if (order2 == 1) {
				if (order1 == 1) {
					int i;
					puts("Please enter the pos do you want insert:");
					cin>>i;
					int num, people;
					double size;
					int condition;
					printf("Please enter the dorm element(num,size,people,condition(1 or 0):\n");
					cin >> num;
					cin >> size;
					cin >> people;
					cin >> condition;
					stu_dorm e(num, size, people, condition);
					ListInsert_L(first_floor, i, e);
					PrintList_L(first_floor);
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;

					/*ListDelete_L(first_floor, i, first_floor.elem[i]);*/
					PrintList_L(first_floor);
				}
				else if (order1 == 3) {
					int i;
					/*puts("Please enter the room number do you want to find");
					cin>>i;
					cout<<"The pos is"<<LocateElem_Sq(first_floor,i,compare);*/
				}
				else if (order1 == 4) {
					PrintList_L(first_floor);
				}
				else {
					puts("ERROR input");
				}
			}
			/*else if(order2==2) {
				if (order1 == 1) {
					int i;
					puts("Please enter the pos do you want insert:");
					cin>>i;
					int num, people;
					double size;
					int condition;
					printf("Please enter the dorm element(num,size,people,condition(1 or 0):\n");
					cin >> num;
					cin >> size;
					cin >> people;
					cin >> condition;
					stu_dorm e(num, size, people, condition);
					ListInsert_Sq(second_floor, i, e);
					Output_Sq(second_floor);
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					ListDelete_Sq(second_floor, i, second_floor.elem[i]);
					Output_Sq(second_floor);
				}
				else if (order1 == 3) {
					int i;
					puts("Please enter the room number do you want to find");
					cin>>i;
					cout<<"The pos is"<<LocateElem_Sq(second_floor,i,compare);
				}
				else if (order1 == 4) {
					Output_Sq(second_floor);
				}
				else {
					puts("ERROR input");
				}
			}*/
			else {
				puts("ERROR input");
			}
		}
		else if (order1 == 5) {
			LinkList all;
			MergeList_L(first_floor, second_floor, all);
			PrintList_L(all);
		}
		else {
			puts("ERROR input");
		}
		putchar(10);
		puts("-----------------------------");
		puts("Please enter the order:");
		menu1();
		cin>>order1;
	}
	
	return 0;
}
