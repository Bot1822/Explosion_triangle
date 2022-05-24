#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cmath>

/* ���õĳ������� */
const double	INF = 1E200;
const double	EP = 1E-10;
const int		MAXV = 300;
const double	PI = 3.14159265;

/* �������νṹ */
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
//ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0 
struct LINE
{
    double a;
    double b;
    double c;
    LINE(double d1 = 1, double d2 = -1, double d3 = 0) { a = d1; b = d2; c = d3; }
};

// ��������֮��ŷ�Ͼ��� 
double dist(POINT p1, POINT p2);
// �ж��������Ƿ��غ�  
bool equal_point(POINT p1, POINT p2);
/******************************************************************************
r=multiply(sp,ep,op),�õ�(sp-op)��(ep-op)�Ĳ��
r>0��ep��ʸ��opsp����ʱ�뷽��
r=0��opspep���㹲�ߣ�
r<0��ep��ʸ��opsp��˳ʱ�뷽��
*******************************************************************************/
double multiply(POINT sp, POINT ep, POINT op);
/*
r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ��
r<0����ʸ���н�Ϊ��ǣ�
r=0����ʸ���н�Ϊֱ�ǣ�
r>0����ʸ���н�Ϊ�۽�
*******************************************************************************/
double dotmultiply(POINT p1, POINT p2, POINT p0);
//�жϵ�p�Ƿ����߶�l��
bool online(LINESEG l, POINT p);
//�жϵ����߶εĹ�ϵ(����)
double relation(POINT p, LINESEG l);
//����ֱ�ߵĹ�ϵ������0Ϊ�ұ�
double relation(POINT p, LINE l);
// ���C���߶�AB����ֱ�ߵĴ��� P 
POINT perpendicular(POINT p, LINESEG l);
// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)  
LINE makeline(POINT p1, POINT p2);
//������֪һ���б�ʣ���ֱ�߷���
LINE makeline(POINT p, double k);
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p  
bool lineintersect(LINE l1, LINE l2, POINT& p); // �� L1��L2 
// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false 
bool intersection(LINESEG l1, LINESEG l2, POINT& inter);
