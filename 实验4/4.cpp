#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

//采用队列管理字符串
typedef char QElemType;
typedef struct QNode {
    QElemType data;
    struct QNode* next;
} QNode, * QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

bool InitQueue(LinkQueue* Q) {
    if(Q == NULL) {
        return false;
    }
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if(!Q->front) {
        exit(-2);
    }
    Q->front->next = NULL;
    return true;
}

bool DestroyQueue(LinkQueue* Q) {
    if(Q == NULL) {
        return false;
    }
    while(Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return true;
}

int QueueLength(LinkQueue Q) {
    int count = 0;
    QueuePtr p = Q.front;
    while(p != Q.rear) {
        count++;
        p = p->next;
    }
    return count;
}


bool GetHead(LinkQueue Q, QElemType* e) {
    QueuePtr p;
    if(Q.front == NULL || Q.front == Q.rear) {
        return false;
    }
    p = Q.front->next;
    *e = p->data;
    return true;
}

bool EnQueue(LinkQueue* Q, QElemType e) {
    QueuePtr p;
    if(Q == NULL || Q->front == NULL) {
        return false;
    }
    p = (QueuePtr) malloc(sizeof(QNode));
    if(!p) {
        exit(-2);
    }
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return true;
}

bool DeQueue(LinkQueue* Q, QElemType* e) {
    QueuePtr p;
    
    if(Q == NULL || Q->front == NULL || Q->front == Q->rear) {
        return false;
    }
    p = Q->front->next;
    *e = p->data;
    
    Q->front->next = p->next;
    if(Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return true;
}

bool QueueTraverse(LinkQueue Q, void (Visit)(QElemType)) {
    QueuePtr p;
    if(Q.front == NULL) {
        return false;
    }
    p = Q.front->next;
    
    while(p != NULL) {
        Visit(p->data);
        p = p->next;
    }
    printf("\n");
    return true;
}

void menu1() {
	puts("1.insert");
	puts("2.delete");
	puts("3.print");
	puts("0.exit");
}

void PrintElem(QElemType e) {
    cout<<e;
}

int main() {
    LinkQueue str;
    puts("Start initialization...");
    InitQueue(&str);
    puts("Please enter the number of the char in the string:");
    int n;cin>>n;
    char tmp;
    for(int i=1;i<=n;i++) {
        cin>>tmp;
        EnQueue(&str,tmp);
    }
    int order1;
	menu1();
	cin>>order1;
    while(order1!=0) {
		if (order1 >= 1 && order1 <= 4) {
				if (order1 == 1) {
					printf("Please enter the char do you want to insert\n");
                    char ch;cin>>ch;
                    EnQueue(&str,ch);
				}
				else if (order1 == 2) {
					char ch;
                    DeQueue(&str,&ch);
				}
				else if (order1 == 3) {
					QueueTraverse(str,PrintElem);
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