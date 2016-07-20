//复杂度O(F|E|) F次深度优先搜索

#define INF 0x3f3f3f3f
#define MAX_V 1000
struct edge{
	int to, cap, rev;
};
vector<edge> G[MAX_V];  //图的邻接表表示  
bool used[MAX_V];      //dfs中用到的访问标记 
//向图中增加一条s到t容量为cap的边 
void add_edge(int from, int to, int cap){
	G[from].push_back((edge){to, cap, G[to].size()});
	G[to].push_back((edge){from, cap, G[from].size()});
}
//dfs寻找增广路 
int dfs(int v, int t, int f){
	if(v == t) return f;
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(!used[e.to] && e.cap > 0){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
//求解s到t的最大流 
int max_flow(int s, int t){
	int flow = 0;
	for( ; ; ){
		memset(used, 0, sizeof(used));
		int f = dfs(s, t, INF);
		if(f == 0) return flow;
		flow += f;
	}
}