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
typedef long long ll;
typedef pair<long long, long long> pll;
pll p[1005];
int cmp(pll a,pll b){
	if(a.first == b.first)
		return a.second < b.second;
	return a.first < b.first; 
}
int power(int B, int L, int P)
{
	int acc = 1, q;
	for(q = L; q; q >>= 1)
	{
		if(q & 1)	acc = (ll)acc * B % P;
		B = (ll)B * B % P;
	}
	return acc;
}
using namespace std;
int main()
{
	int i, j, n, t; 
	map<pll, int> m;
	map<pll, int>::iterator it;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=0;i<n;i++)
			scanf("%lld%lld",&p[i].first,&p[i].second);
		sort(p,p+n,cmp);
		ll res=0;
		for(i = 0; i < n; i++){
			if(i != 0 && p[i] == p[i-1])
				continue;
			for(j = i + 1; j < n; j++){
				ll ix, iy;
				ix = p[j].first - p[i].first;
				iy = p[j].second - p[i].second;
				ll g = __gcd(ix,abs(iy));
				if(g != 0){
					ix/=g;
					iy/=g;
				}
				pll t = make_pair(ix, iy);
				m[t]++;
				}
			for(it = m.begin(); it != m.end(); it++){
				pll tem = it->first;
				if(tem.first == 0 && tem.second == 0){
					res += power(2, it->second + 1, MOD) - it->second - 2;
					res %= MOD;
				}else{
					pll tem1 = make_pair(0, 0);
					ll tk = m[tem1], k;
					k = power(2, it->second, MOD) - 1;
					res += k * (power(2, tk + 1, MOD) - 1);
					res %= MOD;
				}
			}
			m.clear();
		}
		printf("%lld\n",res%MOD);
	} 
    return 0;
}