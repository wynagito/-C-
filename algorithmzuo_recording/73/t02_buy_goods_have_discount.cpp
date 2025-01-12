// 夏季特惠
// 某公司游戏平台的夏季特惠开始了，你决定入手一些游戏
// 现在你一共有X元的预算，平台上所有的 n 个游戏均有折扣
// 标号为 i 的游戏的原价a_i元，现价只要b_i元
// 也就是说该游戏可以优惠 a_i - b_i，并且你购买该游戏能获得快乐值为w_i
// 由于优惠的存在，你可能做出一些冲动消费导致最终买游戏的总费用超过预算
// 只要满足 : 获得的总优惠金额不低于超过预算的总金额
// 那在心理上就不会觉得吃亏。
// 现在你希望在心理上不觉得吃亏的前提下，获得尽可能多的快乐值。
// 测试链接 : https://leetcode.cn/problems/tJau2o/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int MAXN = 501;
const int MAXX = 100001;

// 对于"一定要买的商品"，直接买！
// 只把"需要考虑的商品"放入cost、val数组
int cost[MAXN];
long long val[MAXN];
long long dp[MAXX];

int n, m, x;

long long compute()
{
    std::fill(dp, dp + x + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        for (int j = x; j >= cost[i]; j--)
        {
            dp[j] = std::max(dp[j], dp[j - cost[i]] + val[i]);
        }
    }
    return dp[x];
}

int main()
{
    while (std::cin >> n)
    {
        m = 1;
        std::cin >> x;
        long long ans = 0;
        long long happy = 0;
        for (int i = 1, pre, cur, well; i <= n; i++)
        {
            // 原价
            std::cin >> pre;
            // 现价
            std::cin >> cur;
            // 快乐值
            std::cin >> happy;
            well = pre - cur - cur;
            // 如下是一件"一定要买的商品"
            // 预算 = 100，商品原价 = 10，打折后 = 3
            // 那么好处(well) = (10 - 3) - 3 = 4
            // 所以，可以认为这件商品把预算增加到了104！一定要买！
            // 如下是一件"需要考虑的商品"
            // 预算 = 104，商品原价 = 10，打折后 = 8
            // 那么好处(well) = (10 - 8) - 8 = -6
            // 所以，可以认为这件商品就花掉6元！
            // 也就是说以后花的不是打折后的值，是"坏处"
            if (well >= 0)
            {
                x += well;
                ans += happy;
            }
            else
            {
                cost[m] = -well;
                val[m++] = happy;
            }
        }
        ans += compute();
        std::cout << ans << std::endl;
    }

    return 0;
}
