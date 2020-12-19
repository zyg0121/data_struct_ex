#include <cstdio>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

struct Edge {
    int u, v, w;
} edge[200005];

int fa[5005], n, m, ans, eu, ev, cnt;

inline bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}


inline int find(int x) {
    while (x != fa[x])
        x = fa[x] = fa[fa[x]];
    return x;
}

inline void kruskal() {
    sort(edge, edge + m, cmp);
    //将边的权值排序
    for (int i = 0; i < m; i++) {
        eu = find(edge[i].u), ev = find(edge[i].v);
        if (eu == ev) {
            continue;
        }
        //若出现两个点已经联通了，则说明这一条边不需要了
        printf("edge:(%d,%d),weight = %d\n",eu,ev,edge[i].w);
        ans += edge[i].w;
        //将此边权计入答案
        fa[ev] = eu;
        //将eu、ev合并
        if (++cnt == n - 1) {
            break;
        }
        //循环结束条件，及边数为点数减一时
    }
}
int main() {
    n = 10, m = 30;
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    for (int i = 0; i < m; i++) {
        edge[i].u = rand()%10+1, edge[i].v = rand()%10+1, edge[i].w = rand()%100+1;
    }
    kruskal();
    printf("ans = %d", ans);
    return 0;
}