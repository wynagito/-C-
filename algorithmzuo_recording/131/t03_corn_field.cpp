// 方伯伯的玉米田
// 给定一个长度为n的数组arr
// 每次可以选择一个区间[l,r]，区间内的数字都+1，最多执行k次
// 返回执行完成后，最长的不下降子序列长度
// 1 <= n <= 10^4
// 1 <= arr[i] <= 5000
// 2 <= k <= 500
// 测试链接 : https://www.luogu.com.cn/problem/P3287

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 10001;
const int MAXK = 501;
const int MAXH = 5500;

int arr[MAXN];
int tree[MAXH + 1][MAXK + 1] = {0};
int n, k;

void update(int x, int y, int v)
{
    for (int i = x; i <= MAXH; i += i & -i)
    {
        for (int j = y; j <= k + 1; j += j & -j)
        {
            tree[i][j] = max(tree[i][j], v);
        }
    }
}

int maxfuc(int x, int y)
{
    int ans = 0;
    for (int i = x; i > 0; i -= i & -i)
    {
        for (int j = y; j > 0; j -= j & -j)
        {
            ans = max(ans, tree[i][j]);
        }
    }
    return ans;
}

int compute()
{
    int v, dp;
    // 注意这里第二层for循环，j一定是从k~0的枚举
    // 防止同一个i产生的记录之间相互影响
    for (int i = 1; i <= n; i++)
    {
        for (int j = k; j >= 0; j--)
        {
            v = arr[i] + j;
            dp = maxfuc(v, j + 1) + 1;
            // 修改次数j，树状数组中对应的下标是j+1
            update(v, j + 1, dp);
        }
    }
    // 修改次数k，树状数组中对应的下标是k+1
    return maxfuc(MAXH, k + 1);
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
