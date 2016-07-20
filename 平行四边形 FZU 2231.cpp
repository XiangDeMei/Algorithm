/*
Description
在一个平面内给定n个点，任意三个点不在同一条直线上，用这些点可以构成多少个平行四边形？一个点可以同时属于多个平行四边形。

Input
多组数据（<=10），处理到EOF。

每组数据第一行一个整数n(4<=n<=500)。接下来n行每行两个整数xi,yi(0<=xi,yi<=1e9)，表示每个点的坐标。

Output
每组数据输出一个整数，表示用这些点能构成多少个平行四边形。

Sample Input
4
0 1
1 0
1 1
2 0
Sample Output
1
*/
//找任意两点中点
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <stack>
#include <algorithm>
#include <queue>
#include <map> 
#include <cctype>
#include <queue>
#include <string>
#include <vector>
#include <set>
#include <climits>
#define mst(x,y) memset(x,y,sizeof(x))
#define mcp(x,y) memcpy(x,y,sizeof(y))
using namespace std;
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define PI  atan2(0,-1)
#define eps 1e-8
typedef long long LL;
pair<double, double> p[510],mid;
int main()
{
	int n,i,j,res; 
	map<pair<double, double>, int> m;
	map<pair<double, double>, int>::iterator it;	
	while(~scanf("%d",&n)){
		res=0;
		for(i=0;i<n;i++){
			scanf("%lf%lf",&p[i].first,&p[i].second);
		}
		for(i=0;i<n;i++)
			for(j=i+1;j<n;j++){
				mid.first=(p[i].first+p[j].first)/2.0;
				mid.second=(p[i].second+p[j].second)/2.0;
				m[mid]++;
			} 
		for(it=m.begin();it!=m.end();it++){
			if(it->second>1)
				res+=(it->second-1)*it->second/2;
		}
		printf("%d\n",res);
		m.clear();
	}
	return 0; 
}