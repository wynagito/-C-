// 有依赖的背包(模版)
// 物品分为两大类：主件和附件
// 主件的购买没有限制，钱够就可以；附件的购买有限制，该附件所归属的主件先购买，才能购买这个附件
// 例如，若想买打印机或扫描仪这样的附件，必须先购买电脑这个主件
// 以下是一些主件及其附件的展示：
// 电脑：打印机，扫描仪 | 书柜：图书 | 书桌：台灯，文具 | 工作椅：无附件
// 每个主件最多有2个附件，并且附件不会再有附件，主件购买后，怎么去选择归属附件完全随意，钱够就可以
// 所有的物品编号都在1~m之间，每个物品有三个信息：价格v、重要度p、归属q
// 价格就是花费，价格 * 重要度 就是收益，归属就是该商品是依附于哪个编号的主件
// 比如一件商品信息为[300,2,6]，花费300，收益600，该商品是6号主件商品的附件
// 再比如一件商品信息[100,4,0]，花费100，收益400，该商品自身是主件(q==0)
// 给定m件商品的信息，给定总钱数n，返回在不违反购买规则的情况下最大的收益
// 测试链接 : https://www.luogu.com.cn/problem/P1064
// 测试链接 : https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

const int MAXN = 33001;
const int MAXM = 61;

int cost[MAXM];
int val[MAXM];
bool king[MAXM];
int fans[MAXM];
int follows[MAXM][2];
int dp[MAXN];
int n, m;

void clean()
{
    for (int i = 1; i <= m; i++)
    {
        fans[i] = 0;
    }
}

// 严格位置依赖的动态规划
int compute1()
{
    // dp[0][....] = 0 : 无商品的时候
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    // p : 上次展开的主商品编号
    int p = 0;
    for (int i = 1; i <= m; i++)
    {
        if (king[i])
        {
            for (int j = 0; j <= n; j++)
            {
                // dp[i][j] : 0...i范围上，只关心主商品，并且进行展开
                //            花费不超过j的情况下，获得的最大收益
                // 可能性1 : 不考虑当前主商品
                dp[i][j] = dp[p][j];
                if (j - cost[i] >= 0)
                {
                    // 可能性2 : 考虑当前主商品，只要主
                    dp[i][j] = std::max(dp[i][j], dp[p][j - cost[i]] + val[i]);
                }
                // fan1 : 如果有附1商品，编号给fan1，如果没有，fan1 == -1
                // fan2 : 如果有附2商品，编号给fan2，如果没有，fan2 == -1
                int fan1 = fans[i] >= 1 ? follows[i][0] : -1;
                int fan2 = fans[i] >= 2 ? follows[i][1] : -1;
                if (fan1 != -1 && j - cost[i] - cost[fan1] >= 0)
                {
                    // 可能性3 : 主 + 附1
                    dp[i][j] = std::max(dp[i][j], dp[p][j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                }
                if (fan2 != -1 && j - cost[i] - cost[fan2] >= 0)
                {
                    // 可能性4 : 主 + 附2
                    dp[i][j] = std::max(dp[i][j], dp[p][j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                }
                if (fan1 != -1 && fan2 != -1 && j - cost[i] - cost[fan1] - cost[fan2] >= 0)
                {
                    // 可能性5 : 主 + 附1 + 附2
                    dp[i][j] = std::max(dp[i][j], dp[p][j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
            }
            p = i;
        }
    }
    return dp[p][n];
}

// 空间压缩
int compute2()
{
    std::fill(dp, dp + n + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        if (king[i])
        {
            for (int j = n; j >= cost[i]; j--)
            {
                dp[j] = std::max(dp[j], dp[j - cost[i]] + val[i]);
                int fan1 = fans[i] >= 1 ? follows[i][0] : -1;
                int fan2 = fans[i] >= 2 ? follows[i][1] : -1;
                if (fan1 != -1 && j - cost[i] - cost[fan1] >= 0)
                {
                    dp[j] = std::max(dp[j], dp[j - cost[i] - cost[fan1]] + val[i] + val[fan1]);
                }
                if (fan2 != -1 && j - cost[i] - cost[fan2] >= 0)
                {
                    dp[j] = std::max(dp[j], dp[j - cost[i] - cost[fan2]] + val[i] + val[fan2]);
                }
                if (fan1 != -1 && fan2 != -1 && j - cost[i] - cost[fan1] - cost[fan2] >= 0)
                {
                    dp[j] = std::max(dp[j], dp[j - cost[i] - cost[fan1] - cost[fan2]] + val[i] + val[fan1] + val[fan2]);
                }
            }
        }
    }
    return dp[n];
}

int main()
{
    std::cin >> n >> m;
    clean();
    for (int i = 1; i <= m; i++)
    {
        int v, p, q;
        std::cin >> v >> p >> q;
        cost[i] = v;
        val[i] = v * p;
        king[i] = q == 0;
        if (q != 0)
        {
            follows[q][fans[q]++] = i;
        }
    }
    std::cout << compute2() << std::endl;
    return 0;
}