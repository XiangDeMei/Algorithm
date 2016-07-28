/*
一个矩形，有被若干直线分成N个格子，给出一个点的坐标，问你该点位于哪个点中。
知识点：其实就是点在凸四边形内的判断，若利用叉积的性质，可以二分求解。
*/

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
//#define eps 1e-8
typedef long long LL;

#define sign(x) ((x)>eps?1:((x)<-eps?(-1):(0))) 
const int MAXN=1000;
const double eps=1e-8,inf=1e50 ,Pi=acos(-1.0);
struct point {
    double x,y;
    point() {}
    point(double _x,double _y) {
        x=_x;
        y=_y;
    }
    point operator-(const point &ne)const {
        return point(x-ne.x,y-ne.y);
    }
    point operator+(const point ne)const {
        return point(x+ne.x,y+ne.y);
    }
    point operator*(const double t)const{
        return point(x*t,y*t);
    }
    point operator/(const double t)const{
        if(sign(t)==0)exit(1);
        return point(x/t,y/t);
    }
}up[5000+10],dp[5000+10],p[4];
struct line{
    point a,b;
    line(){}
    line(point _a,point _b){a=_a;b=_b;}
};
double xmult(point o,point a,point b) {
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
//判点在线段上
int p_on_seg(point a,point p1,point p2) {
    if(fabs(xmult(a,p1,p2))<=eps&&(a.x-p1.x)*(a.x-p2.x)<eps&&(a.y-p1.y)*(a.y-p2.y)<eps)
        return 1;
    return 0;
}
//判点在线段端点左方
int p_on_segvex(point s,point p) {
    return fabs(p.y-s.y)<eps&&(p.x<=s.x+eps);
}
//判线段相交 <=:不规范相交
int seg_inter(line s,line p) {
    double minx1=min(s.a.x,s.b.x),maxx1=max(s.a.x,s.b.x);
    double minx2=min(p.a.x,p.b.x),maxx2=max(p.a.x,p.b.x);
    double miny1=min(s.a.y,s.b.y),maxy1=max(s.a.y,s.b.y);
    double miny2=min(p.a.y,p.b.y),maxy2=max(p.a.y,p.b.y);
    if((minx1>maxx2+eps)||(minx2>maxx1+eps)||
            (miny1>maxy2+eps)||(miny2>maxy1+eps))
        return 0;
    else
        return sign(xmult(s.a,s.b,p.a)*xmult(s.a,s.b,p.b))<=0&&
               sign(xmult(p.a,p.b,s.a)*xmult(p.a,p.b,s.b))<=0;
}
//判点在多边形内部
int p_in_polygon(point a,point p[],int n) {
    int count = 0;
    line s,ps;
    ps.a = a,ps.b = a;
    ps.b.x = inf;
    for(int i = 0; i < n; i++) {
        s.a = p[i];
        if(i + 1 < n)s.b = p[i+1];
        else s.b = p[0];
        if (s.a.y > s.b.y)swap(s.a,s.b);
        if (p_on_seg(a,s.a,s.b)) return 2;
        if ((fabs(s.a.y-s.b.y)>eps)) {
            if (p_on_segvex(s.b,a)) count++;
            else if (seg_inter(ps,s))count++;
        }
    }
    if (count%2) return 1;
    return 0;
}
int res[5000+10];
int main()
{
    int n,m,x1,y1,x2,y2;
    while(1){
    	scanf("%d",&n);
    	if(n==0)
    		break;
    	scanf("%d%d%d%d%d",&m,&x1,&y1,&x2,&y2);
    	up[0].x = x1;
    	up[0].y = y1;
    	up[n+1].x = x2;
    	up[n+1].y = y1;
    	dp[0].x = x1;
    	dp[0].y = y2;
    	dp[n+1].x = x2;
    	dp[n+1].y = y2;
    	int u,l;
        for(int i = 1;i <= n; i++){
        	scanf("%d%d",&u,&l);
        	up[i].x = u;
        	up[i].y = y1;
        	dp[i].x = l;
        	dp[i].y = y2;
        }
        memset(res,0,sizeof(res));
        for(int i = 0; i < m; i++){
        	point tp;
        	scanf("%lf%lf",&tp.x,&tp.y);
        	
        	for(int j = 1; j <= n+1; j++){
        		if(dp[j].x<tp.x&&up[j].x<tp.x)
        			continue;
        		p[0]=dp[j-1];
        		p[1]=dp[j];
        		p[2]=up[j];
        		p[3]=up[j-1];
        		if(p_in_polygon(tp,p,4)){
        			res[j-1]++;
        			break;
        		}
        	}
        }
        for(int i = 0; i <= n; i++){
        	printf("%d: %d\n",i,res[i]);
        }
        puts("");
    }
    return 0; 
}