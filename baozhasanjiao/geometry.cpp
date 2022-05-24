#include"geometry.h"

// 返回两点之间欧氏距离 
double dist(POINT p1, POINT p2)
{
    return(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}
// 判断两个点是否重合  
bool equal_point(POINT p1, POINT p2)
{
    return ((abs(p1.x - p2.x) < EP) && (abs(p1.y - p2.y) < EP));
}
/******************************************************************************
r=multiply(sp,ep,op),得到(sp-op)和(ep-op)的叉积
r>0：ep在矢量opsp的逆时针方向；
r=0：opspep三点共线；
r<0：ep在矢量opsp的顺时针方向
*******************************************************************************/
double multiply(POINT sp, POINT ep, POINT op)
{
    return((sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y));
}
/*
r=dotmultiply(p1,p2,op),得到矢量(p1-op)和(p2-op)的点积，如果两个矢量都非零矢量
r<0：两矢量夹角为锐角；
r=0：两矢量夹角为直角；
r>0：两矢量夹角为钝角
*******************************************************************************/
double dotmultiply(POINT p1, POINT p2, POINT p0)
{
    return ((p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y));
}
//判断点p是否在线段l上
bool online(LINESEG l, POINT p)
{
    return((multiply(l.e, p, l.s) == 0) && (((p.x - l.s.x) * (p.x - l.e.x) <= 0) && ((p.y - l.s.y) * (p.y - l.e.y) <= 0)));
}
//判断点与线段的关系(垂足)
double relation(POINT p, LINESEG l)
{
    LINESEG tl;
    tl.s = l.s;
    tl.e = p;
    return dotmultiply(tl.e, l.e, l.s) / (dist(l.s, l.e) * dist(l.s, l.e));
}
//点与直线的关系，大于0为右边
double relation(POINT p, LINE l)
{
    return l.a * p.x + l.b * p.y + l.c;
}
// 求点C到线段AB所在直线的垂足 P 
POINT perpendicular(POINT p, LINESEG l)
{
    double r = relation(p, l);
    POINT tp;
    tp.x = l.s.x + r * (l.e.x - l.s.x);
    tp.y = l.s.y + r * (l.e.y - l.s.y);
    return tp;
}
// 根据已知两点坐标，求过这两点的直线解析方程： a*x+b*y+c = 0  (a >= 0)  
LINE makeline(POINT p1, POINT p2)
{
    LINE tl;
    int sign = 1;
    tl.a = p2.y - p1.y;
    if (tl.a < 0)
    {
        sign = -1;
        tl.a = sign * tl.a;
    }
    tl.b = sign * (p1.x - p2.x);
    tl.c = sign * (p1.y * p2.x - p1.x * p2.y);
    return tl;
}
//根据已知一点和斜率，求直线方程
LINE makeline(POINT p, double k)
{
    LINE tl;
    if (k >= 0) {
        tl.a = k;
        tl.b = -1;
        tl.c = -k * p.x + p.y;
    }
    else {
        tl.a = -k;
        tl.b = 1;
        tl.c = k * p.x - p.y;
    }
    return tl;
}
// 如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)相交，返回true，且返回交点p  
bool lineintersect(LINE l1, LINE l2, POINT& p) // 是 L1，L2 
{
    double d = l1.a * l2.b - l2.a * l1.b;
    if (abs(d) < EP) // 不相交 
        return false;
    p.x = (l2.c * l1.b - l1.c * l2.b) / d;
    p.y = (l2.a * l1.c - l1.a * l2.c) / d;
    return true;
}
// 如果线段l1和l2相交，返回true且交点由(inter)返回，否则返回false 
bool intersection(LINESEG l1, LINESEG l2, POINT& inter)
{
    LINE ll1, ll2;
    ll1 = makeline(l1.s, l1.e);
    ll2 = makeline(l2.s, l2.e);
    if (lineintersect(ll1, ll2, inter))
        return online(l1, inter);
    else
        return false;
}
