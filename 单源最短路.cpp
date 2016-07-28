#define INF 0x3f3f3f3f
#define MAX_V 100005
struct edge{ 
	int from, to;
	int cost;
};
vector<edge> es; //边

int d[MAX_V];   //最短距离 
int V;          //V顶点数 

void add_edge(int from, int to, int cost){
	es.push_back((edge){from, to, cost});
}
//求解从顶点s到其他所有点的最短距离 
void shortest_path(int s){
	for(int i = 0; i < V; i++)
		d[i] = INF;
	d[s] = 0;
	while(true){
		bool update = false;
		for(int i = 0; i < es.size(); i++){
			edge e = es[i];
			if(d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				update = true;
			}
		}
		if(!update) break;
	}
	es.clear();
}