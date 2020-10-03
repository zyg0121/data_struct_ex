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

const int LIST_INIT_SIZE = 100;
const int LISTINCRMENT = 20;

typedef struct {
	stu_dorm *elem;
	int length;
	int listsize;
}SqList;

int IntiList_Sq(SqList &L) {
	L.elem = (stu_dorm *)malloc(LIST_INIT_SIZE * sizeof (stu_dorm));
	if (!L.elem) exit(-2);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return 1;
}

int Input_Sq(SqList &L, int n) {
	stu_dorm *newbase;
	if (n < 0) return false;
	if (n > L.listsize) {
		newbase = (stu_dorm *)malloc(LIST_INIT_SIZE * sizeof (stu_dorm));
		if (!newbase)
			exit(-2);
		L.elem = newbase;
		L.listsize += LISTINCRMENT;
	}
	printf("Please enter the dorm element(num,size,people,condition(1 or 0):\n");
	int num, people;
	double size;
	int condition;
	for (int i = 0; i < n; i++) {
		cin>>num;
		cin>>size;
		cin>>people;
		cin>>condition;
		L.elem[i].set_condition(condition);
		L.elem[i].set_num(num);
		L.elem[i].set_pople(people);
		L.elem[i].set_size(size);
		L.length++; 
	}
	return true;
}

int ListInsert_Sq(SqList &L, int i, stu_dorm e) {
	stu_dorm *newbase;
	if (i<1 || i>L.length + 1) return false;
	if (L.length >= L.listsize) {
		newbase = (stu_dorm *)realloc(L.elem, (L.listsize + LISTINCRMENT) * sizeof(stu_dorm));
		if (!newbase) exit(0);
		L.elem = newbase;
		L.listsize += LISTINCRMENT;
	}
	stu_dorm *q = &(L.elem[i - 1]);
	for (stu_dorm *p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}

int ListDelete_Sq(SqList &L, int i, stu_dorm &e) {
	if (i<1 || i>L.length) return false;
	stu_dorm *p = &(L.elem[i - 1]);
	e = *p;
	stu_dorm *q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	--L.length;
	return true;
}

int LocateElem_Sq(SqList L, int e, int(*compare)(stu_dorm, int)) {
	int i = 1;
	stu_dorm *p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}

int compare(stu_dorm c1,int c2){
	if(c1.get_num()==c2)
		return 1;
	else
		return 0;
}

void MergeList_Sq(SqList La, SqList Lb, SqList &Lc) {
	stu_dorm *pa = La.elem,*pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	stu_dorm *pc = Lc.elem = (stu_dorm*)malloc(Lc.listsize * sizeof(stu_dorm));
	if (!Lc.elem) exit(0);
	stu_dorm *pa_last = La.elem + La.length - 1;
	stu_dorm *pb_last = Lb.elem + Lb.length - 1;
	while (pa <= pa_last) *pc++ = *pa++;
	while (pb <= pb_last) *pc++ = *pb++;
}

int Output_Sq(SqList &L) {
	stu_dorm *p = L.elem;
	stu_dorm *p_last = L.elem + L.length - 1;
	if (!L.elem) exit(0);
	printf("SqList(num,size,people,condition):\n");
	for(int i=0;i<L.length;i++)
		cout<<L.elem[i].get_num()<<' '<<L.elem[i].get_size()<<' '<<L.elem[i].get_people()<<' '<<L.elem[i].get_condition()<<endl;
	return true;
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
	SqList first_floor;
	SqList second_floor;
	puts("Start initialization...");
	puts("Plese enter the first floor dorm element:");
	IntiList_Sq(first_floor);
	int k;
	puts("please enter the number of the rooms");
	cin>>k;
	Input_Sq(first_floor, k);
	puts("Plese enter the second floor dorm element:");
	IntiList_Sq(second_floor);
	puts("please enter the number of the rooms");
	cin>>k;
	Input_Sq(second_floor, k);
	
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
					ListInsert_Sq(first_floor, i, e);
					Output_Sq(first_floor);
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					ListDelete_Sq(first_floor, i, first_floor.elem[i]);
					Output_Sq(first_floor);
				}
				else if (order1 == 3) {
					int i;
					puts("Please enter the room number do you want to find");
					cin>>i;
					cout<<"The pos is"<<LocateElem_Sq(first_floor,i,compare);
				}
				else if (order1 == 4) {
					Output_Sq(first_floor);
				}
				else {
					puts("ERROR input");
				}
			}
			else if(order2==2) {
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
			}
			else {
				puts("ERROR input");
			}
		}
		else if (order1 == 5) {
			SqList all;
			IntiList_Sq(all);
			MergeList_Sq(first_floor, second_floor, all);
			Output_Sq(all);
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
