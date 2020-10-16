#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct QNode {
    long long account;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

bool InitQueue(LinkQueue *Q) {
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

bool EnQueue(LinkQueue &Q,long long &e) {
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(-2);
    p->account = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return true;
}

bool DeQueue(LinkQueue &Q,long long &e) {
    if(Q.front == Q.rear) return false;
    QueuePtr p = Q.front->next;
    e = p->account;
    Q.front->next = p->next;
    if(Q.rear==p) Q.rear = Q.front;
    free(p);
    return true;
}

bool GetHead(LinkQueue &Q, long long& e) {
    QueuePtr p;
    if(Q.front == NULL || Q.front == Q.rear) {
        return false;
    }
    p = Q.front->next;
    e = p->account;
    
    return true;
}


void menu() {
    puts("����в���");
    puts("1.ȡ��");
    puts("2.�к�");
    puts("0.����");
}

int main() {
    LinkQueue bank;
    InitQueue(&bank);
    menu();
    int i;
    long long account = 0;
    cin>>i;
    while(i) {
        printf("ǰ��ʣ��%d��\n",QueueLength(bank));
        GetHead(bank,account);
        if(account==0) cout<<"����һλ"<<endl;
        cout<<"��һλ:"<<account<<endl;
        switch (i) {
            case 1:
                puts("���������Ŀ��ţ�");
                cin>>account;
                EnQueue(bank,account);
                printf("�Ѿ���ʼ�Ŷӣ�ǰ��ʣ��%d��\n",QueueLength(bank));
                break;
            case 2:
                DeQueue(bank,account);
                cout<<"��"<<account<<"��ǰ̨����ҵ��"<<endl;
                break;
            default:
                break;
        }
        menu();
        cin>>i;
    }
    return 0;
}