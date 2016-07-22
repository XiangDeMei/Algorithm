//http://acm.hdu.edu.cn/showproblem.php?pid=1863

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
	int to, cap;
	bool operator< (edge t) const  //排序 
    {
    	return cap > t.cap;
	}
};
vector<edge> G[MAX_V];  //图的邻接表表示  
bool used[MAX_V];      //访问标记 
//向图中增加一条s到t容量为cap的边 
void add_edge(int from, int to, int cap){
	G[from].push_back((edge){to, cap});
	G[to].push_back((edge){from, cap});
}
//堆优化的prime算法 n为节点个数 标号0~n-1 
int prime(int n){
	int ans = 0, isCon = 1;
	priority_queue<edge> q;
	memset(used,false,sizeof(used));
	for(int i = 0; i < G[0].size(); i++){
		q.push(G[0][i]);
	}
	used[0] = true;
	for(int i = 0; i < n; i++)       //n-1条边 
	{
		while(!q.empty())        //每次找边最小的 
		{
			edge t = q.top();
			q.pop();
			if(used[t.to])
				continue;
			ans += t.cap;
			used[t.to] = true;
			isCon++;
			//更新队列
			int l = G[t.to].size(); 
			for(int j = 0;j < l;j++) { 
				edge p = G[t.to][j];
				if(!used[p.to])
					q.push(p);
			}
		}
	}
	if(isCon != n)
		ans = -1;
	return ans;
}

int main()
{
	int n,m;
	int u,v,dis;
	while(1){
		cin>>m>>n; //n为节点数 m为边数 
		if(m==0)
			break;
		for(int i = 0;i < m;i++)
		{
			scanf("%d%d%d",&u,&v,&dis);
			add_edge(u-1, v-1, dis);
		}
		int ans = prime(n);
		if(ans == -1)
			puts("?");
		else
			cout<<ans<<endl;
		for(int i=0;i<n;i++){
			G[i].clear();
		}
	} 
	return 0;
}
