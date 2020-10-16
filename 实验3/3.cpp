#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int STACK_INIT_SIZE = 100;
const int STACKINCREMENT = 10;

typedef struct {
    int x;
    int y;
}PosType;

typedef struct {
    int ord;
    PosType seat;   
    int di;
} SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;

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

bool StackEmpty(SqStack S) {

    if(S.top==S.base) 
        return true;
    else 
        return false;

}

bool Push(SqStack* S, SElemType e) {
    if(S == NULL || S->base == NULL) {
        return false;
    }
    
    if(S->top - S->base >= S->stacksize) {
        S->base = (SElemType*) realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(S->base == NULL) {
            exit(-2);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    
    *(S->top++) = e;
    
    return true;
}

bool Pop(SqStack* S, SElemType* e) {
    if(S == NULL || S->base == NULL) {
        return false;
    }
    
    if(S->top == S->base) {
        return false;
    }

    *e = *(--S->top);
    
    return true;
}

