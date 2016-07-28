#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<algorithm>
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define sign(x) ((x)>eps?1:((x)<-eps?(-1):(0)))
using namespace std;
const int MAXN=1000;
const double eps=1e-8,inf=1e50;
struct point3{
    double x,y,z;
    point3(){}
    point3(double _x,double _y,double _z){
        x=_x;y=_y;z=_z;
    }
    point3 operator-(const point3 &ne){
        return point3(x-ne.x,y-ne.y,z-ne.z);
    }
    point3 operator+(const point3 &ne){
        return point3(x+ne.x,y+ne.y,z+ne.z);
    }
    point3 operator*(const double t){
        return point3(x*t,y*t,z*t);
    }
};
struct line3{
    point3 a,b;
    line3(){}
    line3(point3 _a,point3 _b){
        a=_a;
        b=_b;
    }
};
struct plane3{
    point3 a,b,c;
    plane3(){}
    plane3(point3 _a,point3 _b,point3 _c){
        a=_a;
        b=_b;
        c=_c;
    }
};
point3 xmult(point3 a,point3 b){
    return point3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
double dmult(point3 a,point3 b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}
double lenth(point3 v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}
double dist(point3 a,point3 b){
    return lenth(a-b);
}
double dist2(point3 a,point3 b){
    return dmult(a-b,a-b);
}
//平面法向量
point3 pvec(plane3 s){
    return xmult(s.b-s.a,s.c-s.a);
}
//判定点是否在线段上，包括端点和共线
bool point_on_seg(point3 p,line3 s){
    return sign(lenth(xmult(p-s.a,s.b-s.a)))==0&&(p.x-s.a.x)*(p.x-s.b.x)<eps&&(p.y-s.a.y)*(p.y-s.b.y)<eps&&(p.z-s.a.z)*(p.z-s.b.y)<eps;
}
//判断点在平面上
bool point_on_plane(point3 p,plane3 s){
    return sign(dmult(p-s.a,pvec(s)))==0;
}
//判定点是否在空间三角形上，包括边界，三点共线无意义
bool point_in_triangle( point3 p, plane3 s ) {
    return sign(lenth(xmult(s.a-s.b,s.a-s.c))-lenth(xmult(p-s.a,p-s.b))-lenth(xmult(p-s.b,p-s.c))-lenth(xmult(p-s.c,p-s.a)))!=0;
}
//判定点是否在空间三角形上，不包括边界，三点共线无意义
int point_in_triangle2( point3 p, plane3 s ) {
    return point_in_triangle(p,s)&&lenth(xmult(p-s.a,p-s.b))>eps&&lenth(xmult(p-s.b,p-s.c))>eps&&lenth(xmult(p-s.c,p-s.a))>eps;
}
//判定两点在线段同侧，点在线段上返回0，不共面无意义
bool same_side( point3 p1, point3 p2, line3 l ) {
    return dmult(xmult(l.a-l.b,p1-l.b),xmult(l.a-l.b,p2-l.b))>eps;
}
//判定两点在线段异侧，点在平面上返回0
bool opposite_side( point3 p1, point3 p2, line3 l ) {
    return dmult(xmult(l.a-l.b,p1-l.b),xmult(l.a-l.b,p2-l.b))<-eps;
}
//判定两点在平面同侧，点在平面上返回0
bool same_side( point3 p1, point3 p2, plane3 s ) {
    return dmult(pvec(s),p1-s.a)*dmult(pvec(s),p2-s.a)>eps;
}
//判定两点在平面异侧，点在平面上返回0
bool opposite_side( point3 p1, point3 p2, plane3 s ) {
    return dmult(pvec(s),p1-s.a)*dmult(pvec(s),p2-s.a)<-eps;
}
//判断直线平行
bool parallel(line3 u,line3 v){
    return sign(lenth(xmult(u.b-u.a,v.b-v.a)))==0;
}
//判定两线段相交，不包括端点和部分重合
bool seg_seg_inter( line3 u, line3 v ) {
    return point_on_plane(u.a,plane3(u.b,v.a,v.b))&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
//判定线段与空间三角形相交，包括交于边界和（部分）包含
int seg_triangle_inter( line3 l, plane3 s ) {
    return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,plane3(l.a,l.b,s.c))&&!same_side(s.b,s.c,plane3(l.a,l.b,s.a))&&!same_side(s.c,s.a,plane3(l.a,l.b,s.b));
}
//判定线段与空间三角形相交，不包括交于边界和（部分）包含
int seg_triangle_inter2( line3 l, plane3 s ){
    return opposite_side( l.a, l.b, s ) && opposite_side( s.a, s.b, plane3(l.a, l.b, s.c) ) && opposite_side( s.b, s.c, plane3(l.a, l.b, s.a) ) && opposite_side( s.c, s.a,plane3(l.a, l.b, s.b) );
}
//面面平行
bool parallel(plane3 s1,plane3 s2){
    return sign(lenth(xmult(pvec(s1),pvec(s2))))==0;
}
//判断直线垂直
bool vertical(line3 u,line3 v){
    return sign(dmult(u.b-u.a,v.b-v.a))==0;
}
//面面垂直
bool vertical(plane3 s1,plane3 s2){
    return sign(dmult(pvec(s1),pvec(s2)))==0;
}
//判断两直线的位置关系
int line_to_line(line3 u,line3 v){
    plane3 s1(u.a,u.b,v.a),s2(u.a,u.b,v.b);
    if(sign(lenth(xmult(pvec(s1),pvec(s2)))))
        return -1;//异面
    else if(parallel(u,v))
        return 0;//平行
    else
        return 1;//相交
}
//直线与平面关系
int line_to_plane(line3 u,plane3 s){
    if(sign(dmult(pvec(s),u.b-u.a))==0){
        if(point_on_plane(u.a,s))
            return -1;//直线在平面上
        else
            return 0;//直线平行于平面
    }
    else
        return 1;//线面相交
}
//线面求交
point3 line_plane_intersection(line3 u,plane3 s){
    point3 ret=pvec(s),der=u.b-u.a;
    double t=dmult(ret,s.a-u.a)/dmult(ret,u.b-u.a);
    return u.a+der*t;
}
//线线求交
point3 line_interseciton(line3 u,line3 v){
    point3 ret=u.a,v1=xmult(u.a-v.a,v.b-v.a),v2=xmult(u.b-u.a,v.b-v.a);
    double t=lenth(v1)/lenth(v2)*(dmult(v1,v2)>0?-1:1);
    return ret+((u.b-u.a)*t);
}
//面面求交
line3 plane_intersection(plane3 u,plane3 v){
    line3 ret;
    ret.a=(line_to_plane(line3(v.a,v.b),u)==0)?line_plane_intersection(line3(v.b,v.c),u):line_plane_intersection(line3(v.a,v.b),u);
    ret.b=(line_to_plane(line3(v.c,v.a),u)==0)?line_plane_intersection(line3(v.b,v.c),u):line_plane_intersection(line3(v.a,v.c),u);
    return ret;
}
//点线距离
double dist_point_to_line(point3 p,line3 u){
    return lenth(xmult(p-u.a,u.b-u.a))/dist(u.a,u.b);
}
//点面距离
double dist_point_to_plane(point3 p,plane3 s){
    point3 pv=pvec(s);
    return fabs(dmult(pv,p-s.a))/lenth(pv);
}
//线线距离
double dist_line_to_line(line3 u,line3 v ) {
    point3 p=xmult(u.a-u.b,v.a-v.b);
    return fabs(dmult(u.a-v.a,p))/lenth(p);
}
//点线垂足
point3 vertical_foot(point3 p,line3 u){
    double t=dmult(p-u.a,u.b-u.a)/dist2(u.a,u.b);
    point3 ret=u.a;
    return ret+((u.b-u.a)*t);
}
//已知四面体六边求体积
double volume(double a,double b,double c,double d,double e,double f){
    double a2=a*a,b2=b*b,c2=c*c,d2=d*d,e2=e*e,f2=f*f;
    double tr1=acos((c2+b2-f2)/(2.0*b*c));
    double tr2=acos((a2+c2-e2)/(2.0*a*c));
    double tr3=acos((a2+b2-d2)/(2.0*a*b));
    double tr4=(tr1+tr2+tr3)/2.0;
    double temp=sqrt(sin(tr4)*sin(tr4-tr1)*sin(tr4-tr2)*sin(tr4-tr3));
    return a*b*c*temp/3.0;
}
//四面体体积
double volume(point3 a,point3 b,point3 c,point3 d){
    //abc面方向与d一致时为正
    return fabs(dmult(xmult(b-a,c-a),d-a))/6.0;
}
//三角形面积
double area(double a, double b, double c){
    double p=(a+b+c)/2;
    double s=sqrt(p*(p-a)*(p-b)*(p-c));
    return s;    
}
//四面体内切球球心
point3 centre(point3 a, point3 b, point3 c, point3 d,
			double sbcd, double sacd, double sabd, double sabc) {
	double x, y, z, s;
	s = sbcd + sacd + sabd + sabc;	
	x=(a.x * sbcd + b.x * sacd + c.x * sabd + d.x * sabc)/s;
    y=(a.y * sbcd + b.y * sacd + c.y * sabd + d.y * sabc)/s;
    z=(a.z * sbcd + b.z * sacd + c.z * sabd + d.z * sabc)/s;
    return point3(x, y, z);
}
