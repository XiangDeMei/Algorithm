#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<algorithm>
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)>(b))?(b):(a))
#define sign(x) ((x)>eps?1:((x)<-eps?(-1):(0))) 
using namespace std;
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
};
struct line{
    point a,b;
    line(){}
    line(point _a,point _b){a=_a;b=_b;}
};
struct line2 {
    double a,b,c;
    line2() {}
    line2(double _a,double _b,double _c) {
        a=_a;
        b=_b;
        c=_c;
    }
};
struct circle {
    point o;
    double r;
    circle(){}
    circle(point _o,double _r){
        o=_o;
        r=_r;
    }
};
struct rectangle{
    point a,b,c,d;
    rectangle(){}
    rectangle(point _a,point _b,point _c,point _d){
        a=_a;
        b=_b;
        c=_c;
        d=_d;
    }
};
struct polygon{
    point p[MAXN];
    int n;
};
inline double xmult(point a,point b){
    return a.x*b.y-a.y*b.x;
}
inline double xmult(point o,point a,point b) {
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
inline double xmult(double x1,double y1,double x2,double y2) {
    return x1*y2-x2*y1;
}
inline double dmult(point o,point a,point b) {
    return (a.x-o.x)*(b.x-o.x)+(a.y-o.y)*(b.y-o.y);
}
inline double dmult(point a,point b) {
    return a.x*b.x+a.y*b.y;
}
inline double lenth(point a){
    return sqrt(dmult(a,a));
}
inline double dist(point a,point b){
    return lenth(b-a);
}
inline double dist2(point a,point b){
    return dmult(b-a,b-a);
}
//直线一般式转两点式
line toline(double a,double b,double c) {
    if(sign(b)==0)exit(1);
    point A(0,-c/b),B(-c/a,0);
    return line(A,B);
}
//直线两点式转一般式
line2 toline2(point a,point b) {
    double A=b.y-a.y,B=a.x-b.x,C=-B*a.y-A*a.x;
    return line2(A,B,C);
}
//点p绕o逆时针旋转alpha
point rotate(point o,point p,double alpha) {
    point tp;
    p.x-=o.x;
    p.y-=o.y;
    tp.x=p.x*cos(alpha)-p.y*sin(alpha)+o.x;
    tp.y=p.y*cos(alpha)+p.x*sin(alpha)+o.y;
    return tp;
}
//向量u的倾斜角
double angle(point u) {
    return atan2(u.y,u.x);
}
//oe与os的夹角，夹角正负满足叉积
double angle(point o,point s,point e) {
    point os=s-o,oe=e-o;
    double bot=sqrt(dmult(os,os)*dmult(oe,oe));
    double top=dmult(os,oe);
    double cosfi=top/bot;
    if (cosfi >=  1.0 ) return 0;
    if (cosfi <= -1.0 ) return -Pi;
    double fi=acos(cosfi);
    if(xmult(o,s,e)>0)return fi;
    else return -fi;
}
//p在l上的投影与l关系
double relation(point p,line l) {
    line tl(l.a,p);
    return dmult(tl.b-l.a,l.b-l.a)/dist2(l.a,l.b);
}
//p在l上的垂足
point perpendicular(point p,line l) {
    double r=relation(p,l);
    return l.a+((l.b-l.a)*r);
}
//求点p到线段l的最短距离,并返回线段上距该点最近的点np
double dist_p_to_seg(point p,line l,point &np) {
    double r=relation(p,l);
    if(r<0) {
    np=l.a;
        return dist(p,l.a);
    }
    if(r>1) {
        np=l.b;
        return dist(p,l.b);
    }
    np=perpendicular(p,l);
    return dist(p,np);
}
//求点p到直线l的最短距离
double dist_p_to_line(point p,line l) {
    return abs(xmult(p-l.a,l.b-l.a))/dist(l.a,l.b);
}
//线段之间最短距离
inline double dist_seg_to_seg(line p,line q) {
    return min(min(dist_p_to_seg(p.a,q),dist_p_to_seg(p.b,q)),min(dist_p_to_seg(q.a,p),dist_p_to_seg(q.b,p)));
}
//求矢量线段夹角的余弦
double cosine(line u,line v) {
    point pu=u.b-u.a,pv=v.b-v.a;
    return dmult(pu,pv)/sqrt(dmult(pu,pu)*dmult(pv,pv));
}
//求矢量的夹角的余弦
double cosine(point a,point b){
    return dmult(a,b)/sqrt(dmult(a,a)*dmult(b,b));
}
//求线段夹角
double lsangle(line u,line v) {
    point o(0,0),a=u.b-u.a,b=v.b-v.a;
    return angle(o,a,b);
}
//求直线斜率
double slope(line2 l) {
    if(abs(l.a) < 1e-20)
        return 0;
    if(abs(l.b) < 1e-20)
        return inf;
    return -(l.a/l.b);
}
//直线倾斜角[0,Pi]
double alpha(line2 l) {
    if(abs(l.a)< eps)
        return 0;
    if(abs(l.b)< eps)
        return Pi/2;
    double k=slope(l);
    if(k>0)
        return atan(k);
    else
        return Pi+atan(k);
}
//点关于直线的对称点
point symmetry(line2 l,point p){
   point tp;
   tp.x=((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b);
   tp.y=((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b);
   return tp;
}
//判多边形是否逆时针
bool is_unclock(polygon pg) {
    int n=pg.n;
    pg.p[n]=pg.p[0];
    double area=0;
    for(int i=0; i<n; i++)
        area+=xmult(pg.p[i].x,pg.p[i].y,pg.p[i+1].x,pg.p[i+1].y);
    return area>-eps;
}
//改变多边形时针顺序
void to_unclock(polygon &pg) {
    for(int i=0,j=pg.n-1; i<j; i++,j--)
        swap(pg.p[i],pg.p[j]);
}

//判定凸多边形,顶点按顺时针或逆时针给出,允许相邻边共线
int is_convex(point p[],int n) {
    int i,s[3]= {1,1,1};
    for (i=0; i<n&&s[1]|s[2]; i++)
        s[(sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))+3)%3]=0;
    return s[1]|s[2];
}
//判定凸多边形,顶点按顺时针或逆时针给出,不允许相邻边共线
int is_convex_v2(point p[],int n) {
    int i,s[3]= {1,1,1};
    for (i=0; i<n&&s[0]&&s[1]|s[2]; i++)
        s[(sign(xmult(p[(i+1)%n],p[(i+2)%n],p[i]))+3)%3]=0;
    return s[0]&&s[1]|s[2];
}
//判点在凸多边形内或多边形边上,顶点按顺时针或逆时针给出
int inside_convex(point q,point p[],int n) {
    int i,s[3]= {1,1,1};
    for (i=0; i<n&&s[1]|s[2]; i++)
        s[(sign(xmult(p[(i+1)%n],q,p[i]))+3)%3]=0;
    return s[1]|s[2];
}
//判点在凸多边形内,顶点按顺时针或逆时针给出,在多边形边上返回0
int inside_convex2(point q,point p[],int n) {
    int i,s[3]= {1,1,1};
    for (i=0; i<n&&s[0]&&s[1]|s[2]; i++)
        s[(sign(xmult(p[(i+1)%n],q,p[i]))+3)%3]=0;
    return s[0]&&s[1]|s[2];
}
//判点在线段上
inline int p_on_seg(point a,point p1,point p2) {
    if(fabs(xmult(a,p1,p2))<=eps&&(a.x-p1.x)*(a.x-p2.x)<eps&&(a.y-p1.y)*(a.y-p2.y)<eps)
        return 1;
    return 0;
}
//判点在线段端点左方
inline int p_on_segvex(point s,point p) {
    return fabs(p.y-s.y)<eps&&(p.x<=s.x+eps);
}
//判线段相交 <=:不规范相交
inline int seg_inter(line s,line p) {
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
inline int p_in_polygon(point a,point p[],int n) {
    int count = 0;
    line s,ps;
    ps.a = a,ps.b = a;
    ps.b.x = inf;
    for(int i = 0; i < n; i++) {
        s.a = p[i];
        if(i + 1 < n)s.b = p[i+1];
        else s.b = p[0];
        if (s.a.y > s.b.y)swap(s.a,s.b);
        if (p_on_seg(a,s.a,s.b))return 2;
        if ((fabs(s.a.y-s.b.y)>eps)) {
            if (p_on_segvex(s.b,a)) count++;
            else if (seg_inter(ps,s))count++;
        }
    }
    if (count%2)return 1;
    return 0;
}
//多边形内部最长线段
point stk[MAXN];
double seg_max_len(line u,polygon &pg){
    double ans=0.0,tmp=inf;
    pg.p[pg.n]=pg.p[0];
    int n=pg.n,top=0;
    for(int i=0;i<n;i++){
        line v(pg.p[i],pg.p[i+1]);
        int s1=sign(xmult(u.a,u.b,v.a)),s2=sign(xmult(u.a,u.b,v.b));
        if(s1*s2<=0&&(s1!=0||s2!=0)){
            stk[top++]=line_intersection(u,v);
        }
    }
    stk[top++]=u.a;
    stk[top++]=u.b;
    sort(stk,stk+top);
    top=unique(stk,stk+top)-stk;
    point mp,lp=stk[0];
    for(int i=1;i<top;i++){
        mp=(lp+stk[i])*0.5;
        if(!p_in_polygon(mp,pg))lp=stk[i];
        ans=max(ans,dist2(lp,stk[i]));
    }
    return sqrt(ans);
}
double maxlenth(polygon &pg){
    double ans=0.0;
    for(int i=0;i<pg.n-1;i++){
        for(int j=i+1;j<pg.n;j++){
            ans=max(ans,seg_max_len(line(pg.p[i],pg.p[j]),pg));
            ans=max(ans,seg_max_len(line(pg.p[j],pg.p[i]),pg));
        }
    }
    return ans;
}
//凸包对踵点长度
double opposite_lenth(polygon &pg){
    double ans=inf;
    int a,b,c;
    pg.p[pg.n]=pg.p[0];
    for(a=0,b=1,c=2;a<pg.n;a++,b++){
        while(getarea(pg.p[a],pg.p[b],pg.p[c])<getarea(pg.p[a],pg.p[b],pg.p[(c+1)%pg.n]))c=(c+1)%pg.n;
        ans=min(ans,dist_p_to_line(pg.p[c],line(pg.p[a],pg.p[b])));
    }
    return ans;
}
//判p1,p2是否在l1,l2两侧
inline int opposite_side(point p1,point p2,point l1,point l2) {
    return xmult(l1,l2,p1)*xmult(l1,l2,p2)<-eps;
}
//判线段在任意多边形内,顶点按顺时针或逆时针给出,与边界相交返回1
int seg_in_polygon(point l1,point l2,point p[],int n) {
    point t[MAXN],tt;
    int i,j,k=0;
    if (!p_in_polygon(l1,p,n)||!p_in_polygon(l2,p,n))//不在内部
        return 0;
    for (i=0; i<n; i++)
        if (opposite_side(l1,l2,p[i],p[(i+1)%n])&&opposite_side(p[i],p[(i+1)%n],l1,l2))
            return 0;
        else if (p_on_seg(l1,p[i],p[(i+1)%n]))
            t[k++]=l1;
        else if (p_on_seg(l2,p[i],p[(i+1)%n]))
            t[k++]=l2;
        else if (p_on_seg(p[i],l1,l2))
            t[k++]=p[i];
    for (i=0; i<k; i++)
        for (j=i+1; j<k; j++) {
            tt.x=(t[i].x+t[j].x)/2;
            tt.y=(t[i].y+t[j].y)/2;
            if (!p_in_polygon(tt,p,n))
                return 0;
        }
    return 1;
}
//求直线交点，必须存在交点，或者预判断【解析几何方法】
point line_intersection(line u,line v) { 
    double a1=u.b.y-u.a.y,b1=u.a.x-u.b.x;
    double c1=u.b.y*(-b1)-u.b.x*a1;
    double a2=v.b.y-v.a.y,b2=v.a.x-v.b.x;
    double c2=v.b.y*(-b2)-v.b.x*a2;
    double D=xmult(a1,b1,a2,b2);
    return point(xmult(b1,c1,b2,c2)/D,xmult(c1,a1,c2,a2)/D);
}
//求线段交点，必须存在交点，或者预判断【平面几何方法】
point line_intersection2(line u,line v) { 
    point ret=u.a;
    double t=xmult(u.a-v.a,v.b-v.a)/xmult(u.b-u.a,v.b-v.a);
    t=fabs(t);
    ret.x+=(u.b.x-u.a.x)*t;
    ret.y+=(u.b.y-u.a.y)*t;
    return ret;
}
//三角形重心
point barycenter(point a,point b,point c){
    return (a+b+c)/3.0;
}
//多边形重心
point barycenter(point p[],int n) {
    point ret,t;
    double t1=0,t2;
    int i;
    ret.x=ret.y=0;
    for (i=1; i<n-1; i++)
        if (fabs(t2=xmult(p[i+1],p[0],p[i]))>eps) {
            t=barycenter(p[0],p[i],p[i+1]);
            ret.x+=t.x*t2;
            ret.y+=t.y*t2;
            t1+=t2;
        }
    if (fabs(t1)>eps)
        ret.x/=t1,ret.y/=t1;
    return ret;
}
//求多边形面积
inline double getarea(point pg[],int n) {
    double area=0;
    pg[n]=pg[0];
    for(int i=0; i<n; i++)
        area+=xmult(pg[i].x,pg[i].y,pg[i+1].x,pg[i+1].y);
    return fabs(area)/2.0;
}
//解方程ax^2+bx+c=0
int equaltion(double a,double b,double c,double &x1,double &x2) {
    double der=b*b-4*a*c;
    switch(sign(der)) {
    case -1:
        return 0;
    case 0:
        x1=-b/(2*a);
        return 1;
    case 1:
        der=sqrt(der);
        x1=(-b-der)/(2*a);
        x2=(-b+der)/(2*a);
        return 2;
    }
}
//线段与圆交点
int line_circle_intersection(line u,circle c,point &p1,point &p2) {
    double dis=lenth(u.b-u.a);
    point d=(u.b-u.a)/dis;
    point E=c.o-u.a;
    double a=dmult(E,d);
    double a2=a*a;
    double e2=dmult(E,E);
    double r2=c.r*c.r;
    if((r2-e2+a2)<0){
        return 0;
    } else {
        double f=sqrt(r2 - e2 + a2);
        double t=a-f;
        int cnt=0;
        if(t>-eps&&t-dis<eps){//去掉后面变成射线
            p1=u.a+(d*t);
            cnt++;
        }
        t=a+f;
        if(t>-eps&&t-dis<eps) {
            p2=u.a+(d*t);
            cnt++;
        }
        return cnt;
    }
}
//给出在任意多边形内部的一个点
point a_point_in_polygon(polygon pg) {
    point v,a,b,r;
    int i,index;
    v=pg.p[0];
    index=0;
    for(i=1; i<pg.n; i++) { 
        if(pg.p[i].y<v.y) {
            v=pg.p[i];
            index=i;
        }
    }
    a=pg.p[(index-1+pg.n)%pg.n];
    b=pg.p[(index+1)%pg.n];
    point q;
    polygon tri;
    tri.n=3;
    tri.p[0]=a;
    tri.p[1]=v;
    tri.p[2]=b;
    double md=inf;
    int in1=index;
    bool bin=false;
    for(i=0; i<pg.n; i++) {
        if(i == index)continue;
        if(i == (index-1+pg.n)%pg.n)continue;
        if(i == (index+1)%pg.n)continue;
        if(!inside_convex2(pg.p[i],tri.p,3))continue;

        bin=true;
        if(dist(v,pg.p[i])<md) {
            q=pg.p[i];
            md=dist(v,q);
        }
    }
    if(!bin) {
        r.x=(a.x+b.x)/2;
        r.y=(a.y+b.y)/2;
        return r;
    }
    r.x=(v.x+q.x)/2;
    r.y=(v.y+q.y)/2;
    return r;
}
//求在多边形外面的点到凸包的切点
void p_cut_polygon(point p,polygon pg,point &rp,point &lp) {
    line ep,en;
    bool blp,bln;
    rp=pg.p[0];
    lp=pg.p[0];
    for(int i=1; i<pg.n; i++) {
        ep.a=pg.p[(i+pg.n-1)%pg.n];
        ep.b=pg.p[i];
        en.a=pg.p[i];
        en.b=pg.p[(i+1)%pg.n];
        blp=xmult(ep.b-ep.a,p-ep.a)>=0;
        bln=xmult(en.b-en.a,p-en.a)>=0;
        if(!blp&&bln) {
            if(xmult(pg.p[i]-p,rp-p)>0)
                rp=pg.p[i];
        }
        if(blp&&!bln) {
            if(xmult(lp-p,pg.p[i]-p)>0)
                lp=pg.p[i];
        }
    }
    return ;
}
//判断点p在圆c内
bool p_in_circle(point p,circle c) {
    return c.r*c.r>dist2(p,c.o);
}
//求矩形第4个点
point rect4th(point a,point b,point c) {
    point d;
    if(abs(dmult(a-c,b-c))<eps) {
        d=a+b-c;
    }
    if(abs(dmult(a-b,c-b))<eps) {
        d=a+c-b;
    }
    if(abs(dmult(c-a,b-a))<eps) {
        d=c+b-a;
    }
    return d;
}
//判两圆关系
int CircleRelation(circle c1,circle c2){
    double d=lenth(c1.o-c2.o);
    if( fabs(d-c1.r-c2.r) < eps )
        return 2;//外切
    if( fabs(d-fabs(c1.r-c2.r)) < eps )
        return 4;//内切
    if( d > c1.r+c2.r )
        return 1;//相离
    if( d < fabs(c1.r-c2.r) )
        return 5;//内含
    if( fabs(c1.r-c2.r) < d && d < c1.r+c2.r)
        return 3;//相交
    return 0; //error!
}
//判圆与矩形关系,矩形水平
bool Circle_In_Rec(circle c,rectangle r) {
    if( r.a.x < c.o.x && c.o.x < r.b.x && r.c.y < c.o.y && c.o.y < r.b.y ) {
        line line1(r.a, r.b);
        line line2(r.b, r.c);
        line line3(r.c, r.d);
        line line4(r.d, r.a);
        if(c.r<dist_p_to_line(c.o,line1)&&c.r<dist_p_to_line(c.o,line2)&&c.r<dist_p_to_line(c.o,line3)&&c.r<dist_p_to_line(c.o,line4))
            return true;
    }
    return false;
}
//射线关于平面的反射
void reflect(line2 u,line2 v,line2 &l){
    double n,m;
    double tpb,tpa;
    tpb=u.b*v.b+u.a*v.a;
    tpa=v.a*u.b-u.a*v.b;
    m=(tpb*u.b+tpa*u.a)/(u.b*u.b+u.a*u.a);
    n=(tpa*u.b-tpb*u.a)/(u.b*u.b+u.a*u.a);
    if(fabs(u.a*v.b-v.a*u.b)<1e-20) {
        l.a=v.a;
        l.b=v.b;
        l.c=v.c;
        return;
    }
    double xx,yy; //(xx,yy)是入射线与镜面的交点。
    xx=(u.b*v.c-v.b*u.c)/(u.a*v.b-v.a*u.b);
    yy=(v.a*u.c-u.a*v.c)/(u.a*v.b-v.a*u.b);
    l.a=n;
    l.b=-m;
    l.c=m*yy-xx*n;
}
//两圆交点（预判断不相交情况）
void c2point(circle c1,circle c2,point &rp1,point &rp2) {
    double a,b,r;
    a=c2.o.x-c1.o.x;
    b=c2.o.y-c1.o.y;
    r=(a*a+b*b+c1.r*c1.r-c2.r*c2.r)/2;
    if(a==0&&b!=0) {
        rp1.y=rp2.y=r/b;
        rp1.x=sqrt(c1.r*c1.r-rp1.y*rp1.y);
        rp2.x=-rp1.x;
    } else if(a!=0&&b==0) {
        rp1.x=rp2.x=r/a;
        rp1.y=sqrt(c1.r*c1.r-rp1.x*rp2.x);
        rp2.y=-rp1.y;
    } else if(a!=0&&b!=0) {
        double delta;
        delta=b*b*r*r-(a*a+b*b)*(r*r-c1.r*c1.r*a*a);
        rp1.y=(b*r+sqrt(delta))/(a*a+b*b);
        rp2.y=(b*r-sqrt(delta))/(a*a+b*b);
        rp1.x=(r-b*rp1.y)/a;
        rp2.x=(r-b*rp2.y)/a;
    }
    rp1=rp1+c1.o;
    rp2=rp2+c1.o;
}
//圆外一点引圆的切线
void cutpoint(circle c,point sp,point &rp1,point &rp2) {
    circle c2;
    c2.o=(c.o+sp)/2.0;
    c2.r=lenth(c2.o-sp);
    c2point(c,c2,rp1,rp2);
}
//圆c1上，与c2的外切点
void c2cuto(circle c1, circle c2, point &p1, point &p2) {
    double d = dist(c1.o, c2.o), dr = c1.r - c2.r;
    double b = acos(dr / d);
    double a = angle(c2.o-c1.o);
    double a1 = a - b, a2 = a + b;
    p1=point(cos(a1) * c1.r, sin(a1) * c1.r) + c1.o;
    p2=point(cos(a2) * c1.r, sin(a2) * c1.r) + c1.o;
}
//圆c1上，与c2的内切点
void c2cuti(circle c1,circle c2,point &p1,point &p2){
    point dr=c2.o-c1.o;
    dr=dr/lenth(dr);
    point a=c1.o-(dr*c1.r),b=c1.o+(dr*c1.r);
    point c=c2.o-(dr*c2.r),d=c2.o+(dr*c2.r);
    circle E((a+c)/2.0,lenth(c-a)/2.0),F((b+d)/2.0,lenth(d-b)/2.0);
    point q1,q2;
    c2point(E,F,q1,q2);
    point L=line_intersection2(line(c1.o,c2.o),line(q1,q2));
    circle c3((c1.o+L)/2.0,lenth(L-c1.o)/2.0);
    c2point(c1,c3,p1,p2);
}

//极角排序
//1.利用叉积的正负来作cmp.(即是按逆时针排序).
bool cmp(const point &a, const point &b)//逆时针排序 
{
    point origin;
    origin.x = origin.y = 0;
    return cross(origin,b,origin,a) < 0;
}
//2.利用complex的内建函数。
#include<complex>
#define x real()
#define y imag()
#include<algorithm>
using namespace std;
bool cmp(const Point& p1, const Point& p2)
{
    return arg(p1) < arg(p2);
}
//3.atan2函数
//4.利用象限加上极角，叉积。
bool cmp(const point &a, const point &b)//先按象限排序，再按极角排序，再按远近排序 
{
    if (a.y == 0 && b.y == 0 && a.x*b.x <= 0)return a.x>b.x;
    if (a.y == 0 && a.x >= 0 && b.y != 0)return true;
    if (b.y == 0 && b.x >= 0 && a.y != 0)return false;
    if (b.y*a.y <= 0)return a.y>b.y;
    point one;
    one.y = one.x = 0;
    return cross(one,a,one,b) > 0 || (cross(one,a,one,b) == 0 && a.x < b.x);    
}
