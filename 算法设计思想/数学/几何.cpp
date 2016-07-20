#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<stack>
#include<algorithm>
#include<queue>
#include<map> 
typedef long long ll;
using namespace std;


#define infinity 1e20
#define EP 1e-10
const int MAXV = 300 ;
const double PI = 2.0*asin(1.0); //高精度求PI
struct Lpoint {double x,y;}; //点
struct Llineseg{Lpoint a,b; }; //线段
struct Ldir{double dx,dy;}; //方向向量
struct Lline{Lpoint p; Ldir dir;}; //直线  点+方向向量 
struct Lrad{Lpoint Sp; Ldir dir;}; //射线
struct Lround{Lpoint co; double r;};//圆

int Euqal_Point(Lpoint p1,Lpoint p2)//判断两点是否相等  精度 
{
	return((fabs(p1.x-p2.x)<EP)&&(fabs(p1.y-p2.y)<EP));
}
double pTop(Lpoint p1,Lpoint p2)//两点之间距离 
{
	return (sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y)));
}
/*
(P1-P0)*(P2-P0)的叉积
若结果为正，则<P0,P1>在<P0,P2>的顺时针方向；
若为0则<P0,P1><P0,P2>共线；
若为负则<P0,P1>在<P0,P2>的在逆时针方向;
可以根据这个函数确定两条线段在交点处的转向,
比如确定p0p1和p1p2在p1处是左转还是右转，只要求
(p2-p0)*(p1-p0)，若<0则左转，>0则右转，=0则共线
*/
double xmulti(Lpoint p1,Lpoint p2,Lpoint p0)//叉积 
{
	return	((p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y));
}
void format(Lline ln,double& A,double& B,double& C)//计算直线的一般式 Ax+By+C=0
{
	A=ln.dir.dy;
	B=-ln.dir.dx;
	C=ln.p.y*ln.dir.dx-ln.p.x*ln.dir.dy;
}
double pTol(Lpoint a,Lline ln)//点到直线距离
{
	double A, B, C;
	format(ln, A, B, C);
	return(fabs(A * a.x + B * a.y + C) / sqrt( A * A + B * B));
}

/*
	Graham 求凸包 O(N * logN)
	int graham(point pnt[], int n, point res[])
	pnt[]传入点集，顺序无要求，n为点的个数
	res[]用来保存凸包中的点,逆时针排序，大小要比pnt[]大1，可能所有点都属于凸包
	函数返回凸包中点的个数,个数可能为n,所以res[]需要定义n+1大小
*/

struct point{double x,y;} p[N],res[N+1];//res[]用来保存凸包中的点

bool mult(point sp, point ep, point op){
	return (sp.x-op.x)*(ep.y-op.y)>=(ep.x - op.x)*(sp.y-op.y);
}
bool operator < (const point &l, const point &r){
	return l.y < r.y || (l.y == r.y && l.x < r.x);
}
int graham(point pnt[], int n, point res[]){
	int i, len, k = 0, top = 1;
	sort(pnt, pnt + n);
	if (n == 0) 	return 0; 
	res[0] = pnt[0];
	if (n == 1) 	return 1; 
	res[1] = pnt[1];
	if (n == 2) 	return 2; 
	res[2] = pnt[2];
	for (i = 2; i < n; i++) {
		while (top && mult(pnt[i], res[top], res[top-1]))
			top--;
		res[++top] = pnt[i];
	}
	len = top; 
	res[++top] = pnt[n - 2];
	for (i = n - 3; i >= 0; i--) {
		while (top!=len && mult(pnt[i], res[top],res[top-1])) 
			top--;
		res[++top] = pnt[i];
	}
	return top; // 返回凸包中点的个数
}
int main()
{
	Lpoint a,b,c;
	Lline l;
	scanf("%lf%lf%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y,&c.x,&c.y);
	l.p=b;
	l.dir.dx=c.x-b.x;
	l.dir.dy=c.y-b.y;
	cout<<pTol(a,l)<<endl;
	return 0;
}