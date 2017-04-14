#include <set>
#include <map>
#include <queue>
#include <deque>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

#define INF 0x3f3f3f3f
#define MAX_V 100005
struct edge{
	int to,cap,cost,rev;
};
int V;
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

//向图中增加一条s到t容量为cap的边 
void add_edge(int from, int to, int cap, int cost){
	G[from].push_back((edge){to, cap, cost, G[to].size()});
	G[to].push_back((edge){from, 0, 0-cost, G[from].size() - 1});
}

int min_cost_flow(int s, int t, int f){
	int res = 0;
	while(f > 0){
		fill(dist, dist + V, INF);
		dist[s] = 0;
		bool update = true;
		while(update){
			update = false;
			for(int v = 0; v < V; v++){
				if(dist[v] == INF) continue;
				for(int i = 0; i < G[v].size(); i++){
					edge &e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i;
						update = true;
					}
				}
			}
		}
		
		if(dist[t] == INF){
			return -1;
		}	
		
		int d = f;
		for(int v = t; v != s; v = prevv[v]){
			d = min(d, G[prevv[v]][preve[v]].cap);
		}

		f -= d;
		res += d * dist[t];
		for(int v = t; v != s; v = prevv[v]){
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}

int main()
{
	int n,m;
	int u,v,dis;
	while(~scanf("%d%d",&n,&m)){
		V = n + n;
		add_edge(0, n, 2, 0);
		add_edge(n-1, n+n-1, 2, 0);
		for(int i = 1; i < n-1; i++) {
              add_edge(i, i+n, 1,0);
          }
		for(int i=0;i<m;i++){
			int u,v,cost;
			scanf("%d%d%d",&u,&v,&cost);
			add_edge(u+n-1, v-1, 1,cost);	
		}
		int res = min_cost_flow(0, n+n-1, 2);
		printf("%d\n",res);
		for(int i = 0;i < m + n; i++){
			G[i].clear();
		}
	} 
	return 0;
}
