#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

typedef struct QNode {
    string name;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

bool InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front) exit(-2);
    Q.front->next = NULL;
    return true;
}

bool QueueEmpty(LinkQueue Q) {
    if(Q.front == Q.rear) {
        return true;
    } else {
        return false;
    }
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

bool DestroyQueue(LinkQueue &Q) {
    while(Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return true;
}

bool EnQueue(LinkQueue &Q,string &e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(-2);
    p->name = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}

bool DeQueue(LinkQueue &Q,string &e) {
    if(Q.front == Q.rear) return false;
    QueuePtr p = Q.front->next;
    e = p->name;
    Q.front->next = p->next;
    if(Q.rear==p) Q.rear = Q.front;
    free(p);
    return true;
}

bool GetHead(LinkQueue Q, string& e) {
    QueuePtr p;
    if(Q.front == NULL || Q.front == Q.rear) {
        return false;
    }
    p = Q.front->next;
    e = p->name;
    
    return true;
}

void menu() {
    puts("请进行操作");
    puts("1.取号");
    puts("2.叫号");
    puts("0.结束");
}

int main() {
    LinkQueue bank;
    InitQueue(bank);
    menu();
    int i;
    string name,enname,dename;
    cin>>i;
    while(i) {
        printf("前方剩余%d人\n",QueueLength(bank));
        GetHead(bank,name);
        if(name=="") cout<<"无下一位"<<endl;
        cout<<"下一位:"<<name<<endl;
        switch (i) {
        case 1:
            puts("请输入您的姓名：");
            cin>>enname;
            EnQueue(bank,enname);
            printf("已经开始排队，前方剩余%d人\n",QueueLength(bank));
            break;
        case 2:
            DeQueue(bank,dename);
            cout<<"请"<<dename<<"到前台办理业务"<<endl;
            break;
        default:
            break;
        }
        menu();
        cin>>i;
    }
    return 0;
}