#include"geometry.h"

// ��������֮��ŷ�Ͼ��� 
double dist(POINT p1, POINT p2)
{
    return(sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}
// �ж��������Ƿ��غ�  
bool equal_point(POINT p1, POINT p2)
{
    return ((abs(p1.x - p2.x) < EP) && (abs(p1.y - p2.y) < EP));
}
/******************************************************************************
r=multiply(sp,ep,op),�õ�(sp-op)��(ep-op)�Ĳ��
r>0��ep��ʸ��opsp����ʱ�뷽��
r=0��opspep���㹲�ߣ�
r<0��ep��ʸ��opsp��˳ʱ�뷽��
*******************************************************************************/
double multiply(POINT sp, POINT ep, POINT op)
{
    return((sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y));
}
/*
r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ��
r<0����ʸ���н�Ϊ��ǣ�
r=0����ʸ���н�Ϊֱ�ǣ�
r>0����ʸ���н�Ϊ�۽�
*******************************************************************************/
double dotmultiply(POINT p1, POINT p2, POINT p0)
{
    return ((p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y));
}
//�жϵ�p�Ƿ����߶�l��
bool online(LINESEG l, POINT p)
{
    return((multiply(l.e, p, l.s) == 0) && (((p.x - l.s.x) * (p.x - l.e.x) <= 0) && ((p.y - l.s.y) * (p.y - l.e.y) <= 0)));
}
//�жϵ����߶εĹ�ϵ(����)
double relation(POINT p, LINESEG l)
{
    LINESEG tl;
    tl.s = l.s;
    tl.e = p;
    return dotmultiply(tl.e, l.e, l.s) / (dist(l.s, l.e) * dist(l.s, l.e));
}
//����ֱ�ߵĹ�ϵ������0Ϊ�ұ�
double relation(POINT p, LINE l)
{
    return l.a * p.x + l.b * p.y + l.c;
}
// ���C���߶�AB����ֱ�ߵĴ��� P 
POINT perpendicular(POINT p, LINESEG l)
{
    double r = relation(p, l);
    POINT tp;
    tp.x = l.s.x + r * (l.e.x - l.s.x);
    tp.y = l.s.y + r * (l.e.y - l.s.y);
    return tp;
}
// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)  
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
//������֪һ���б�ʣ���ֱ�߷���
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
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p  
bool lineintersect(LINE l1, LINE l2, POINT& p) // �� L1��L2 
{
    double d = l1.a * l2.b - l2.a * l1.b;
    if (abs(d) < EP) // ���ཻ 
        return false;
    p.x = (l2.c * l1.b - l1.c * l2.b) / d;
    p.y = (l2.a * l1.c - l1.a * l2.c) / d;
    return true;
}
// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false 
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
