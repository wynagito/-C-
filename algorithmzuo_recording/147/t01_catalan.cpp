// 卡特兰数模版
// 进栈顺序规定为1、2、3..n，返回有多少种不同的出栈顺序
// 测试题目的数据量很小，得到的卡特兰数没有多大，不需要取模处理
// 但是请假设，当n比较大时，卡特兰数是很大的，答案对 1000000007 取模
// 测试链接 : https://www.luogu.com.cn/problem/P1044

#include <iostream>
#include <vector>
#include <algorithm>

const int MOD = 1000000007;
const int MAXN = 1000001;

// 阶乘余数表
long long fac[MAXN];

// 阶乘逆元表
long long inv1[MAXN];

// 连续数逆元表
long long inv2[MAXN];

long long power(long long a, long long b);

// 生成阶乘余数表、阶乘逆元表
void build1(int n)
{
    fac[0] = inv1[0] = 1;
    fac[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        fac[i] = (1LL * i * fac[i - 1]) % MOD;
    }
    inv1[n] = power(fac[n], MOD - 2);
    for (int i = n - 1; i >= 1; i--)
    {
        inv1[i] = (1LL * (i + 1) * inv1[i + 1]) % MOD;
    }
}

// 生成连续数逆元表
void build2(int n)
{
    inv2[1] = 1;
    for (int i = 2; i <= n + 1; i++)
    {
        inv2[i] = (MOD - inv2[MOD % i] * (MOD / i) % MOD + MOD) % MOD;
    }
}

long long power(long long x, long long p)
{
    long long ans = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            ans = (ans * x) % MOD;
        }
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ans;
}

long long c(int n, int k)
{
    return (((fac[n] * inv1[k]) % MOD) * inv1[n - k]) % MOD;
}

// 公式1
long long compute1(int n)
{
    build1(2 * n);
    return (c(2 * n, n) - c(2 * n, n - 1) + MOD) % MOD;
}

// 公式2
long long compute2(int n)
{
    build1(2 * n);
    return c(2 * n, n) * power(n + 1, MOD - 2) % MOD;
}

// 公式3
long long compute3(int n)
{
    build2(n);
    std::vector<long long> f(n + 1);
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i - 1] * (4 * i - 2) % MOD * inv2[i + 1] % MOD;
    }
    return f[n];
}

// 公式4
long long compute4(int n)
{
    std::vector<long long> f(n + 1);
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int l = 0, r = i - 1; l < i; l++, r--)
        {
            f[i] = (f[i] + f[l] * f[r] % MOD) % MOD;
        }
    }
    return f[n];
}

int main()
{
    int n;
    std::cin >> n;
    std::cout << compute1(n) << std::endl;
    // std::cout << compute2(n) << std::endl;
    // std::cout << compute3(n) << std::endl;
    // std::cout << compute4(n) << std::endl;
    return 0;
}