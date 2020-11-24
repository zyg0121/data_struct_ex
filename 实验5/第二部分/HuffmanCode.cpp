#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

class HuffmanCode {
    public :
        string ch;
        int grade;
        deque<int> Huffcode;
};

class HuffmanNode {
    public:
        int w;
        HuffmanNode *fa;
        HuffmanNode *lc;
        HuffmanNode *rc;
};

struct cmp {
    bool operator() (const HuffmanNode *a,const HuffmanNode *b) {
        return a->w >b->w;
    }
};

void Huff_init(priority_queue<HuffmanNode*,vector<HuffmanNode*>,cmp> &pq,int n) {
    for(int i = 0;i < n-1;i++) {
        if(pq.size() == 1)
            break;
        
        HuffmanNode *pnode = new HuffmanNode;
        HuffmanNode *lnode = pq.top();
        pq.pop();
        HuffmanNode *rnode = pq.top();
        pq.pop();
        
        pnode->fa = NULL;
        pnode->w = lnode->w+rnode->w;
        pnode->lc = lnode;
        pnode->rc = rnode;
        lnode->fa = pnode;
        rnode->fa = pnode;

        pq.push(pnode);
    }
}

void Huff_code(HuffmanNode *node,HuffmanCode *code,int n) {
    for(int i = 0;i < n;i++) {
        HuffmanNode *curnode = &node[i];
        while (true)
        {
            if(curnode->fa == NULL) {
                break;
            } else {
                if(curnode->fa->rc == curnode)
                    code[i].Huffcode.push_front(1);
                else 
                    code[i].Huffcode.push_front(0);
            }
            curnode = curnode->fa;
        }
        
    }
}

void Huff_print(HuffmanCode *code,int n) {
    for(int i = 0;i < n;i++) {
        cout<<code[i].ch<<" 's grade is:"<<code[i].grade<<" and Huffman code is:";
        for(deque<int>::iterator it = code[i].Huffcode.begin();it != code[i].Huffcode.end();it++) 
            cout<<*it;
        putchar(10);
    }
}

const int max_stu = 1000+10;
HuffmanCode code[max_stu];
HuffmanNode node[max_stu];

int main() {
    int n;
    puts("Please enter the number of the student:");
    cin>>n;
    puts("Please enter the name and grade of the students:");
    for(int i = 0;i < n;i++) {
        cin>>code[i].ch>>code[i].grade;
        node[i].fa = NULL;
        node[i].lc = node[i].rc =NULL;
    }

    priority_queue<HuffmanNode*,vector<HuffmanNode*>,cmp> pq;
    for(int i = 0;i < n;i++) 
        pq.push(node+i);
    
    Huff_init(pq,n);
    Huff_code(node,code,n);
    Huff_print(code,n);
    
    return 0;
}