#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

//采用字符串管理字符串

string str;

void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.find");
	puts("4.print");
	puts("0.exit");
}

int main() {
    string str;
    puts("Start initialization...");
    puts("please enter the string");
    getline(cin,str);
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
                    string e;
                    cin>>e;
                    str.insert(i,e);
                    cout<<str<<endl;
				}
				else if (order1 == 2) {
					int i;
					puts("Please enter the pos do you want delete:");
					cin >> i;
					str.erase(i,1);
                    cout<<str<<endl;
				}
				else if (order1 == 3) {
					int i;
					puts("Please enter the pos do you want to find");
					cin>>i;
                    i--;
                    string tmp=str.substr(i,1);
					cout<<"The char is "<<tmp;
				}
				else if (order1 == 4) {
					cout<<str;
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