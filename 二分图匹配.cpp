#define MAX_V 1000
int v;                 //顶点数 
vector<int> G[MAX_V];  //图的邻接表表示 
int match[MAX_V];      //所匹配的顶点 
bool used[MAX_V];      //dfs中用到的访问标记 
//向图中增加一条连接u v的边 
void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
//dfs寻找增广路 
bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}
//求解二分图最大匹配 
int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int vi = 0; vi < v; vi++){
		if(match[vi] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(vi)){
				res++;
			}
		}
	}
	return res;
}