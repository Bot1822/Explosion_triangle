#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cmath>

/* 常用的常量定义 */
const double	INF = 1E200;
const double	EP = 1E-10;
const int		MAXV = 300;
const double	PI = 3.14159265;

/* 基本几何结构 */
struct POINT
{
    double x;
    double y;
    POINT(double a = 0, double b = 0) { x = a; y = b; } //constructor 
};
struct LINESEG
{
    POINT s;
    POINT e;
    LINESEG(POINT a, POINT b) { s = a; e = b; }
    LINESEG() { }
};
//直线的解析方程 a*x+b*y+c=0  为统一表示，约定 a >= 0 
struct LINE
{
    double a;
    double b;
    double c;
    LINE(double d1 = 1, double d2 = -1, double d3 = 0) { a = d1; b = d2; c = d3; }
};

// 返回两点之间欧氏距离 
double dist(POINT p1, POINT p2);
// 判断两个点是否重合  
bool equal_point(POINT p1, POINT p2);
/******************************************************************************
r=multiply(sp,ep,op),得到(sp-op)和(ep-op)的叉积
r>0：ep在矢量opsp的逆时针方向；
r=0：opspep三点共线；
r<0：ep在矢量opsp的顺时针方向
*******************************************************************************/
double multiply(POINT sp, POINT ep, POINT op);
/*
r=dotmultiply(p1,p2,op),得到矢量(p1-op)和(p2-op)的点积，如果两个矢量都非零矢量
r<0：两矢量夹角为锐角；
r=0：两矢量夹角为直角；
r>0：两矢量夹角为钝角
*******************************************************************************/
double dotmultiply(POINT p1, POINT p2, POINT p0);
//判断点p是否在线段l上
bool online(LINESEG l, POINT p);
//判断点与线段的关系(垂足)
double relation(POINT p, LINESEG l);
//点与直线的关系，大于0为右边
double relation(POINT p, LINE l);
// 求点C到线段AB所在直线的垂足 P 
POINT perpendicular(POINT p, LINESEG l);
// 根据已知两点坐标，求过这两点的直线解析方程： a*x+b*y+c = 0  (a >= 0)  
LINE makeline(POINT p1, POINT p2);
//根据已知一点和斜率，求直线方程
LINE makeline(POINT p, double k);
// 如果两条直线 l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)相交，返回true，且返回交点p  
bool lineintersect(LINE l1, LINE l2, POINT& p); // 是 L1，L2 
// 如果线段l1和l2相交，返回true且交点由(inter)返回，否则返回false 
bool intersection(LINESEG l1, LINESEG l2, POINT& inter);
