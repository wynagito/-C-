// 最长递增子序列和最长不下降子序列
// 给定一个整数数组nums
// 找到其中最长严格递增子序列长度、最长不下降子序列长度
// 测试链接 : https://leetcode.cn/problems/longest-increasing-subsequence/

class Solution
{
public:
    // 普通解法的动态规划
    // 时间复杂度O(n^2)，数组稍大就会超时
    int lengthOfLIS1(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            dp[i] = 1;
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    // 最优解
    // 时间复杂度O(n * logn)
    int lengthOfLIS2(vector<int> &nums)
    {
        int n = nums.size();
        // ends[i] 目前所有长度为i+1的递增子序列的最小结尾
        vector<int> ends(n, 0);
        // len表示ends数组目前的有效区长度
        // ends[0...len-1]是有效区，有效区内的数字一定严格升序
        int len = 0;
        for (int i = 0, find; i < n; i++)
        {
            find = bs1(ends, len, nums[i]);
            if (find == -1)
            {
                ends[len++] = nums[i];
            }
            else
            {
                ends[find] = nums[i];
            }
        }
        return len;
    }

    // "最长递增子序列"使用如下二分搜索 :
    // ends[0...len-1]是严格升序的，找到>=num的最左位置
    // 如果不存在返回-1
    int bs1(vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (ends[m] >= num)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }

    // 如果求最长不下降子序列，那么使用如下的二分搜索 :
    // ends[0...len-1]是不降序的
    // 在其中找到>num的最左位置，如果不存在返回-1
    // 如果求最长不下降子序列，就在lengthOfLIS中把bs1方法换成bs2方法
    // 已经用对数器验证了，是正确的
    int bs2(vector<int> &ends, int len, int num)
    {
        int l = 0, r = len - 1, m, ans = -1;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (ends[m] > num)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        return ans;
    }
};