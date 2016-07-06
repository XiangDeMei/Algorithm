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
double xmulti(Lpoint p1,Lpoint p2,Lpoint p0)
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