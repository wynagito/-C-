// 可以用r、e、d三种字符拼接字符串，如果拼出来的字符串中
// 有且仅有1个长度>=2的回文子串，那么这个字符串定义为"好串"
// 返回长度为n的所有可能的字符串中，好串有多少个
// 结果对1000000007取模， 1 <= n <= 10^9
// 示例：
// n = 1, 输出0
// n = 2, 输出3
// n = 3, 输出18

#include <iostream>

using namespace std;

int f(char *path, int i, int n);
bool is(char *s, int l, int r);

// 暴力方法
// 为了观察规律
int num1(int n)
{
    char *path = new char[n];
    return f(path, 0, n);
}

int f(char *path, int i, int n)
{
    if (i == n)
    {
        int cnt = 0;
        for (int l = 0; l < n; l++)
        {
            for (int r = l + 1; r < n; r++)
            {
                if (is(path, l, r))
                {
                    cnt++;
                }
                if (cnt > 1)
                {
                    return 0;
                }
            }
        }
        return cnt == 1 ? 1 : 0;
    }
    else
    {
        // i正常位置
        int ans = 0;
        path[i] = 'r';
        ans += f(path, i + 1, n);
        path[i] = 'e';
        ans += f(path, i + 1, n);
        path[i] = 'd';
        ans += f(path, i + 1, n);
        return ans;
    }
}

bool is(char *s, int l, int r)
{
    while (l < r)
    {
        if (s[l] != s[r])
        {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

// 正式方法
// 观察规律之后变成代码
int num2(int n)
{
    if (n == 1)
    {
        return 0;
    }
    if (n == 2)
    {
        return 3;
    }
    if (n == 3)
    {
        return 18;
    }
    return (int)(((long long)6 * (n + 1)) % 1000000007);
}

int main()
{
    for (int i = 1; i <= 10; i++)
    {
        cout << "长度为" << i << ", 答案:" << num1(i) << endl;
    }
    return 0;
}