// 休息k分钟最大会议和
// 给定一个长度为n的数组arr，表示从早到晚发生的会议，各自召开的分钟数
// 当选择一个会议并参加之后，必须休息k分钟
// 返回能参加的会议时长最大累加和
// 比如，arr = { 200, 5, 6, 14, 7, 300 }，k = 15
// 最好的选择为，选择200分钟的会议，然后必须休息15分钟
// 那么接下来的5分钟、6分钟、14分钟的会议注定错过
// 然后放弃7分钟的会议，而选择参加300分钟的会议
// 最终返回500
// 1 <= n、arr[i]、k <= 10^6
// 来自真实大厂笔试，对数器验证

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 不减少枚举的可能性
// 时间复杂度O(n^2)
long best1(const vector<int> &arr, int k)
{
    int n = arr.size();
    // dp[i] 表示从第i个会议往后的最大累加和
    vector<long> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        int j;
        long sum = 0;
        for (j = i + 1; j < n && sum < k; j++)
        {
            sum += arr[j];
        }
        // 选择第i个会议， dp[j] + arr[i]
        // 跳过第i个会议， dp[i + 1]
        dp[i] = max(dp[i + 1], dp[j] + arr[i]);
    }
    return dp[0];
}

// 利用预处理结构减少枚举的可能性
// 时间复杂度O(n)
long best2(const vector<int> &arr, int k)
{
    int n = arr.size();
    // jump[i] 如果选择了i号会议，则跳到jump[i]号会议
    vector<int> jump(n);

    // 窗口[l...r)，左闭右开，sum是窗口累加和
    for (int i = 0, l = 1, r = 1, sum = 0; i < n - 1; i++, l++)
    {
        while (r < n && sum < k)
        {
            sum += arr[r++];
        }
        jump[i] = r;
        sum -= arr[l];
    }
    jump[n - 1] = n;

    vector<long> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = max(dp[i + 1], dp[jump[i]] + arr[i]);
    }
    return dp[0];
}

// 为了测试
vector<int> randomArray(int n, int v)
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % v + 1;
    }
    return arr;
}

// 为了测试
int main()
{
    int n = 1000;
    int v = 3000;
    int testTime = 10000;
    cout << "测试开始" << endl;

    for (int i = 1; i <= testTime; i++)
    {
        int size = rand() % n + 1;
        vector<int> arr = randomArray(size, v);
        int k = rand() % v + 1;
        long ans1 = best1(arr, k);
        long ans2 = best2(arr, k);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
    }

    cout << "测试结束" << endl;

    return 0;
}