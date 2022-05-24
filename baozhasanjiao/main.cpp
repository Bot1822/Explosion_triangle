#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include "geometry.h"

using namespace std;

map< string, double[4] > boom_25;
//初始化常见可燃气体爆炸上下限表（25℃）
void init_boom_25()
{
    boom_25["CH4"][0] = 5.00;
    boom_25["CH4"][1] = 15.00;
    boom_25["CH4"][2] = 5.1;
    boom_25["CH4"][3] = 61.0;
    boom_25["C2H6"][0] = 3.22;
    boom_25["C2H6"][1] = 12.45;
    boom_25["C2H6"][2] = -1;
    boom_25["C2H6"][3] = -1;
    boom_25["C3H8"][0] = 2.4;
    boom_25["C3H8"][1] = 9.50;
    boom_25["C3H8"][2] = 2.3;
    boom_25["C3H8"][3] = 52.0;
    boom_25["H2"][0] = 4.00;
    boom_25["H2"][1] = 74.20;
    boom_25["H2"][2] = 4.00;
    boom_25["H2"][3] = 94.0;
    boom_25["CO"][0] = 12.5;
    boom_25["CO"][1] = 75.00;
    boom_25["CO"][2] = 15.5;
    boom_25["CO"][3] = 94.0;
    boom_25["H2S"][0] = 4.32;
    boom_25["H2S"][1] = 45.50;
    boom_25["H2S"][2] = -1;
    boom_25["H2S"][3] = -1;
    boom_25["C2H4"][0] = 2.75;
    boom_25["C2H4"][1] = 28.60;
    boom_25["C2H4"][2] = 3.0;
    boom_25["C2H4"][3] = 80.0;
    boom_25["C5H12"][0] = 1.40;
    boom_25["C5H12"][1] = 7.80;
    boom_25["C5H12"][2] = -1;
    boom_25["C5H12"][3] = -1;
}

class boom
{
private:
    map<string, double> MixC;
    double O, sum, temperature, C_NL, C_NU, C_NL_O, C_NU_O, OU, OL, OP, NP;
    POINT U1, U2, L1, L2, Linjie;
    map< string, double[4] > boom_T;
    int area = -1;
    /* data */
public:
    void init();
    //更新当前温度下的可燃气体爆炸表
    void updateBoomT();
    //计算混合气体的爆炸上下限
    void computeMixLU();
    //更新三角形上四个点
    void updateLUpoint();
    //计算临界氧浓度等各项数值
    void computeC();
    //判断临界区
    void judgeArea();
    boom(/* args */);
    ~boom();
};

void boom::init()
{
    double temp = 0;
    cout << "请输入各可燃气体浓度(如不存在该气体则输入0)(省略%)" << endl;
    for (auto t : boom_25) {
        cout << t.first << ": ";
        cin >> temp;
        if (temp) MixC[t.first] = temp;
        sum += temp;
    }
    cout << "请输入当前温度：";
    cin >> temperature;
    cout << "请输入当前氧气含量：(省略%)";
    cin >> O;
}

void boom::updateBoomT()
{
    for (auto p : MixC) {
        string str = p.first;
        for (int i = 0; i < 4; ++i) {
            if (boom_25[str][i] == -1) boom_T[str][i] = -1;
            else if (i == 0 || i == 2) boom_T[str][i] = boom_25[str][i] * (1 - 721 * (temperature - 25) / 1000000);
            else boom_T[str][i] = boom_25[str][i] * (1 + 721 * (temperature - 25) / 1000000);
        }
    }
}

void boom::computeMixLU()
{
    double temp1 = 0, temp1_O = 0, temp2 = 0, temp2_O = 0;
    for (auto p : boom_T) {
        temp1 += MixC[p.first] * 100 / sum / p.second[0];
        temp2 += MixC[p.first] * 100 / sum / p.second[1];
        temp1_O += MixC[p.first] * 100 / sum / p.second[2];
        temp2_O += MixC[p.first] * 100 / sum / p.second[3];
    }
    C_NL = 100 / temp1;
    C_NU = 100 / temp2;
    C_NL_O = 100 / temp1_O;
    C_NU_O = 100 / temp2_O;
}

void boom::updateLUpoint()
{
    double x = C_NU_O / 2;
    double y = sqrt(3) * C_NU_O / 2;
    U2 = POINT(x, y);
    x = C_NL_O / 2;
    y = sqrt(3) * C_NL_O / 2;
    L2 = POINT(x, y);
    x = 79.05 - 29.05 * C_NU / 100;
    y = sqrt(3) * C_NU / 2;
    U1 = POINT(x, y);
    x = 79.05 - 29.05 * C_NL / 100;
    y = sqrt(3) * C_NL / 2;
    L1 = POINT(x, y);
}

void boom::computeC()
{
    LINE x = LINE(0, 1, 0);
    LINE U2U1, L2L1, la, lb, lc;
    U2U1 = makeline(U2, U1);
    L2L1 = makeline(L2, L1);
    lineintersect(U2U1, L2L1, Linjie);
    la = makeline(Linjie, -sqrt(3));
    POINT a, b, c;
    lineintersect(la, x, a);
    LINE U1b = makeline(U1, -sqrt(3));
    LINE L1c = makeline(L1, -sqrt(3));
    lineintersect(U1b, x, b);
    lineintersect(L1c, x, c);
    OP = 100 - a.x;
    OU = 100 - b.x;
    OL = 100 - c.x;
    POINT F = POINT(50, 50 * sqrt(3)), A = POINT(79.05, 0);
    LINESEG AF = LINESEG(A, F);
    NP = relation(Linjie, AF) * 100;
}

void boom::judgeArea()
{
    if (sum < 0 || O < 0) {
        cout << "error!!!";
        return;
    }
    POINT p(sum, O);
    LINE ae, be, bc, ce;
    POINT a(20.95, 0), b(C_NL, OL), c(C_NU, OU), e(NP, OP);
    ae = makeline(a, e);
    be = makeline(b, e);
    bc = makeline(b, c);
    ce = makeline(c, e);
    if (relation(p, ae) < 0) area = 2;
    else if (relation(p, be) > 0 && relation(p, bc) < 0 && relation(p, ce) < 0) area = 1;
    else if (relation(p, ce) > 0 && relation(p, bc) < 0) area = 3;
    else area = 0;
}

boom::boom(/* args */)
{
    init();
    updateBoomT();
    computeMixLU();
    updateLUpoint();
    computeC();
    judgeArea();
    cout << "爆炸上限氧浓度：" << OU << endl;
    cout << "爆炸下限氧浓度：" << OL << endl;
    cout << "临界氧浓度：" << OP << endl;
    cout << "此时可燃性混合气体浓度为：" << NP << endl;
    cout << "当前状态处于第" << area << "区" << endl;
}

boom::~boom()
{
}

int main()
{
    init_boom_25();
    boom();
    return 0;
}