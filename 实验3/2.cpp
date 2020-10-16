#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int STACK_INIT_SIZE = 100;
const int STACKINCREMENT = 10;

typedef char SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
} SqStack;

bool InitStack(SqStack* S) {
    if(S == NULL) {
        return false;
    }
    
    S->base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(S->base == NULL) {
        exit(-2);
    }
    
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    
    return true;
}

bool DeleteStack(SqStack* S) {

    if(S == NULL) {
        return false;
    }

    free((*S).base);
    S->base = NULL;
    S->top = NULL;
    S->stacksize = 0;

    return true;
}

bool StackEmpty(SqStack S) {

    if(S.top==S.base) 
        return true;
    else 
        return false;

}

int StackLength(SqStack S) {
    if(StackEmpty(S)==true) 
        return 0;
    else 
        return (int)(S.top-S.base);
}

bool GetTop(SqStack S,SElemType *e) {
    if(StackEmpty(S)==true)
        return false;
    else {
        *e = *(S.top-1);
        return true;
    }
}

bool Push(SqStack* S, SElemType e) {
    if(S == NULL || (*S).base == NULL) {
        return false;
    }
    
    if((*S).top - (*S).base >= (*S).stacksize) {
        (*S).base = (SElemType*) realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if((*S).base == NULL) {
            exit(-2);
        }
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    
    *(S->top++) = e;
    
    return true;
}

bool Pop(SqStack* S, SElemType* e) {
    if(S == NULL || (*S).base == NULL) {
        return false;
    }
    
    if((*S).top == (*S).base) {
        return false;
    }

    *e = *(--(*S).top);
    
    return true;
}

int main() {
    SqStack S;
    SElemType e;
    int n;
    InitStack(&S);
    puts("Please enter the number of the elem:");
    cin>>n;
    puts("Please enter the elem:");
    for(int i=1;i<=n;i++) {
        cin>>e;
        Push(&S,e);
    }
    puts("The out is :");
    for(int i=1;i<=n;i++) {
        GetTop(S,&e);
        cout<<e<<' ';
        Pop(&S,&e);
    }
    return 0;

}