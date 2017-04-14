#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 100100;  
struct edge  
{  
    int to, cost, next;  
}g[N*2];  
  
int dp[20][N*2];  
//dp[i][j]记录的是以j为起点、2的i次方长度内的深度最小点的编号，因为访问2n-1次，数组长度要乘2  
int n, m;  
int cnt, tot, head[N];  
bool vis[N];  
int dep[N*2], ver[N*2], fir[N], dis[N];   
//ver为访问的节点依次编号，dep记录编号对应的节点的深度，因为访问2n-1次，所有这两个数组长度乘2    
void add_edge(int v, int u, int cost)  
{  
    g[cnt].to = u, g[cnt].cost = cost, g[cnt].next = head[v], head[v] = cnt++;  
}  
void dfs(int v, int cur)  
{  
    vis[v] = true, ver[++tot] = v, dep[tot] = cur, fir[v] = tot;  
    for(int i = head[v]; i != -1; i = g[i].next)  
    {  
        int u = g[i].to;  
        if(! vis[u])  
        {  
            dis[u] = dis[v] + g[i].cost;  
            dfs(u, cur + 1);  
            ver[++tot] = v, dep[tot] = cur;  
        }  
    }  
}  
void ST(int n)  
{  
    for(int i = 1; i <= n; i++)  
        dp[0][i] = i;  
    for(int i = 1; (1<<i) <= n; i++)  
        for(int j = 1; j <= n - (1<<i) + 1; j++)  
            dp[i][j] = dep[dp[i-1][j]] < dep[dp[i-1][j+(1<<(i-1))]] ? dp[i-1][j] : dp[i-1][j+(1<<(i-1))];  
}  
int rmq(int v, int u)  
{  
    int k = (int)log2(u - v + 1);  
    return dep[dp[k][v]] < dep[dp[k][u-(1<<k)+1]] ? dp[k][v] : dp[k][u-(1<<k)+1];  
}  
int lca(int v, int u)  
{  
    v = fir[v], u = fir[u];  
    if(v > u) swap(v, u);  
    int res = rmq(v, u);  
    return ver[res];  
}  
int get_dis(int u,int v)
{ 
    return dis[u]+dis[v]-2*dis[lca(u,v)];
}

int main()
{
    int t,k=1,tu,tv,tw,q;
    scanf("%d",&t);
    while(t--){
    	scanf("%d%d",&n,&q);
    	cnt = 0;  
        memset(head, -1, sizeof head);
    	for(int i=0;i<n-1;i++){
    		int u,v,w;
    		scanf("%d%d%d",&u,&v,&w);
    		add_edge(u, v, w);  
            add_edge(v, u, w);  
    	}
    	memset(vis, 0, sizeof vis);  
        dis[1] = 0;  
        tot = 0;  
        dfs(1, 1);  
        ST(2 * n - 1); 
        
        // for(int i=0;i<2*n-1;i++){
        //     printf("%d ",dep[i]); 
        // }
        // printf("\n");
        // for(int i=0;i<2*n-1;i++){
        //     printf("%d ",ver[N*2]);
        // }
        // printf("\n");

    	scanf("%d%d%d",&tu,&tv,&tw);
    	printf("Case #%d:\n",k);
    	for(int i=0;i<q;i++){
    		int u,v,lca;
            scanf("%d%d",&u,&v);
            int dis,dis1,dis2;
            dis = get_dis(u,v);
            dis1 = get_dis(u,tu)+tw+get_dis(tv,v);
            dis2 = get_dis(u,tv)+tw+get_dis(tu,v);
            int res = dis - min(dis1,dis2);
            if(res<0)
            	res=0;
            printf("%d\n",res);
    	}	
    	k++;
    }
    return 0;
}
