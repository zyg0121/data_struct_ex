#include<cstdio>
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<cstring>
using namespace std;

const int Max_n=1001;
vector<int>G[Max_n];
int use[Max_n];

void dfs(int v){
	printf("%d ",v);//输出当前遍历的结点 
	use[v]=1;//标记 
	while(!G[v].empty()){//该结点有邻接点 
		int v1=G[v].back();//从邻接表中取出 
		G[v].pop_back();// 删除 
		if(!use[v1])//取出的结点是否使用过 
			dfs(v1);//未使用过继续向下递归 
	}
}
int main(){
	int v=10,e=30;
	memset(use,0,sizeof(use));
    srand(time(NULL));
	for(int i=1;i<=e;i++){
		int from,to;
        from = rand()%10+1;
        to = rand()%10+1;
		G[from].push_back(to);//建立邻接表 
		G[to].push_back(from);  
	} 
	dfs(1);
	return 0;
} 