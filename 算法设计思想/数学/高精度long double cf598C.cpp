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
#define inf 0x3f3f3f3f
#define PI  atan2(0,-1)
typedef long long LL;
struct f{
	int id;
	long double dg;
}ans[100000+10];
int cmp(f a, f b){
	return a.dg<b.dg;
}
int main()
{
	int n,i,x,y,loc;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>x>>y;
		ans[i].id=i+1;
		ans[i].dg=atan2(y,x);
		if(ans[i].dg<0)
			ans[i].dg+=2*PI;
	}
	sort(ans,ans+n,cmp);
	long double tem,min=ans[0].dg-ans[n-1].dg+2*PI; 
	loc=0;
	for(i=1;i<n;i++){
		tem=ans[i].dg-ans[i-1].dg;
		if(tem<min){
			min=tem;
			loc=i;
		}
	}
	if(loc==0)
		cout<<ans[loc].id<<" "<<ans[n-1].id<<endl;
	else
		cout<<ans[loc].id<<" "<<ans[loc-1].id<<endl;
	return 0; 
}