#include <iostream>
#include <vector>

using namespace std;

const int MOD = 7; // 题目会保证取模的数字为质数
const int MAXN = 101;

int mat[MAXN][MAXN];
int inv[MOD];

// 逆元线性递推公式求逆元表
void computeInverse()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; i++)
    {
        inv[i] = (MOD - (long long)inv[MOD % i] * (MOD / i) % MOD) % MOD;
    }
}

// 求a和b的最大公约数，保证a和b都不等于0
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// 高斯消元解决同余方程组模版
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // 已经成为主元的行不参与
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }
            // 找到系数不等于0的行做主元即可
            if (mat[j][i] != 0)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] != 0)
                {
                    int gcdValue = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcdValue;
                    int b = mat[j][i] / gcdValue;
                    if (j < i && mat[j][j] != 0)
                    {
                        for (int k = j; k < i; k++)
                        {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
                    }
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] != 0)
        {
            bool flag = false;
            for (int j = i + 1; j <= n; j++)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

// 结果矩阵打印
void print(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "========================" << endl;
}

int main()
{
    // 逆元表建立好
    computeInverse();

    cout << "课上图解的例子，唯一解" << endl;
    // 4*x1 + 2*x2 + 4*x3 同余 3
    // 2*x1 + 5*x2 + 2*x3 同余 2
    // 6*x1 + 3*x2 + 4*x3 同余 5
    mat[1][1] = 4;
    mat[1][2] = 2;
    mat[1][3] = 4;
    mat[1][4] = 3;
    mat[2][1] = 2;
    mat[2][2] = 5;
    mat[2][3] = 2;
    mat[2][4] = 2;
    mat[3][1] = 6;
    mat[3][2] = 3;
    mat[3][3] = 4;
    mat[3][4] = 5;
    gauss(3);
    print(3);

    cout << "表达式存在矛盾的例子" << endl;
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 5
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1;
    mat[1][2] = 2;
    mat[1][3] = 3;
    mat[1][4] = 2;
    mat[2][1] = 2;
    mat[2][2] = 4;
    mat[2][3] = 6;
    mat[2][4] = 5;
    mat[3][1] = 0;
    mat[3][2] = 3;
    mat[3][3] = 4;
    mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "课上图解的例子，多解" << endl;
    cout << "只有确定了自由元，才能确定主元的值" << endl;
    cout << "如果是多解的情况，那么在消元结束后" << endl;
    cout << "二维矩阵中主元和自由元的关系是正确的" << endl;
    // 1*x1 + 2*x2 + 3*x3 同余 2
    // 2*x1 + 4*x2 + 6*x3 同余 4
    // 0*x1 + 3*x2 + 4*x3 同余 2
    mat[1][1] = 1;
    mat[1][2] = 2;
    mat[1][3] = 3;
    mat[1][4] = 2;
    mat[2][1] = 2;
    mat[2][2] = 4;
    mat[2][3] = 6;
    mat[2][4] = 4;
    mat[3][1] = 0;
    mat[3][2] = 3;
    mat[3][3] = 4;
    mat[3][4] = 2;
    gauss(3);
    print(3);

    cout << "注意下面这个多解的例子" << endl;
    // 1*x1 + 1*x2 + 1*x3 同余 3
    // 2*x1 + 1*x2 + 1*x3 同余 5
    // 0*x1 + 3*x2 + 3*x3 同余 3
    mat[1][1] = 1;
    mat[1][2] = 1;
    mat[1][3] = 1;
    mat[1][4] = 3;
    mat[2][1] = 2;
    mat[2][2] = 1;
    mat[2][3] = 1;
    mat[2][4] = 5;
    mat[3][1] = 0;
    mat[3][2] = 3;
    mat[3][3] = 3;
    mat[3][4] = 3;
    gauss(3);
    print(3);

    cout << "最后一个例子里" << endl;
    cout << "主元x1，不受其他自由元影响，值可以直接确定" << endl;
    cout << "但是主元x2，受到自由元x3的影响，6*x2 + 6*x3 同余 6" << endl;
    cout << "只有自由元x3确定了值，主元x2的值才能确定" << endl;
    cout << "本节课提供的模版，对于能求出的主元可以得到正确结果" << endl;
    cout << "对于不能求出的主元，该模版也能给出，主元和自由元的正确关系" << endl;

    return 0;
}
