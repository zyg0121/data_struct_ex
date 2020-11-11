#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

//采用顺序表管理字符串

class str {
private:
	char str_ch;
public:
	str() {}
	str(char ch) {
		str_ch = ch;
	}
	~str(){}
	char get_ch() {
		return str_ch;
	}
	void set_ch(char ch) {
		str_ch = ch;
	}
};

const int LIST_INIT_SIZE = 100;
const int LISTINCRMENT = 20;

typedef struct {
	str *elem;
	int length;
	int listsize;
}SqList;

int IntiList_Sq(SqList &L) {
	L.elem = (str *)malloc(LIST_INIT_SIZE * sizeof (str));
	if (!L.elem) exit(-2);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return 1;
}

int Input_Sq(SqList &L, int n) {
	str *newbase;
	if (n < 0) return false;
	if (n > L.listsize) {
		newbase = (str *)malloc(LIST_INIT_SIZE * sizeof (str));
		if (!newbase)
			exit(-2);
		L.elem = newbase;
		L.listsize += LISTINCRMENT;
	}
	printf("Please enter the char\n");
	char ch;
	for (int i = 0; i < n; i++) {
		cin>>ch;
		L.elem[i].set_ch(ch);
		L.length++; 
	}
	return true;
}

int ListInsert_Sq(SqList &L, int i, str e) {
	str *newbase;
	if (i<1 || i>L.length + 1) return false;
	if (L.length >= L.listsize) {
		newbase = (str *)realloc(L.elem, (L.listsize + LISTINCRMENT) * sizeof(str));
		if (!newbase) exit(0);
		L.elem = newbase;
		L.listsize += LISTINCRMENT;
	}
	str *q = &(L.elem[i - 1]);
	for (str *p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L.length;
	return true;
}

int ListDelete_Sq(SqList &L, int i, str &e) {
	if (i<1 || i>L.length) return false;
	str *p = &(L.elem[i - 1]);
	e = *p;
	str *q = L.elem + L.length - 1;
	for (++p; p <= q; ++p) *(p - 1) = *p;
	--L.length;
	return true;
}

int LocateElem_Sq(SqList L, int e, int(*compare)(str, char)) {
	int i = 1;
	str *p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) return i;
	else return 0;
}

int compare(str c1,char c2){
	if(c1.get_ch()==c2)
		return 1;
	else
		return 0;
}

int Output_Sq(SqList &L) {
	str *p = L.elem;
	str *p_last = L.elem + L.length - 1;
	if (!L.elem) exit(0);
	for(int i=0;i<L.length;i++)
		cout<<L.elem[i].get_ch()<<' ';
	return true;
}

void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.find");
	puts("4.print");
	puts("0.exit");
}

int main() {
    SqList str;
    puts("Start initialization...");
	IntiList_Sq(str);
    puts("please enter the number of the char");
    int k;cin>>k;
    Input_Sq(str, k);
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
					ListInsert_Sq(str, i, e);
					Output_Sq(str);
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					ListDelete_Sq(str, i, str.elem[i]);
					Output_Sq(str);
				}
				else if (order1 == 3) {
					char i;
					puts("Please enter the pos do you want to find");
					cin>>i;
					cout<<"The pos is "<<LocateElem_Sq(str,i,compare);
				}
				else if (order1 == 4) {
					Output_Sq(str);
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