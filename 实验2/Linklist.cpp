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