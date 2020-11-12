#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib> 
using namespace std;

//采用数组管理字符串

const int max_str = 2000+10;

char str[max_str];
int cnt;

void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.find");
	puts("4.print");
	puts("0.exit");
}

void Insert(int x,char e) {
    for(int i=cnt+1;i>=x;i--)
        str[i]=str[i-1];
    str[x]=e;
}

void Delete(int x) {
    for(int i=x+1;i<=cnt;i++)
        str[i-1]=str[i];
    
}

void Output() {
    for(int i=1;i<=cnt;i++)
        cout<<str[i];
    cout<<endl;
}

int main() {
    puts("Start initialization...");
    puts("please enter the number(<1000) of the char");
    cin>>cnt;
    puts("please enter the string:");
    for(int i=1;i<=cnt;i++)
        cin>>str[i];
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
					Insert(i, e);cnt++;
					Output();
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					Delete(i);cnt--;
					Output();
				}
				else if (order1 == 3) {
					int i;
					puts("Please enter the pos do you want to find");
					cin>>i;
					cout<<str[i]<<endl;
				}
				else if (order1 == 4) {
					Output();
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