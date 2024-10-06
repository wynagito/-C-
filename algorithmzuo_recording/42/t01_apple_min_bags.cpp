// 对数器打表找规律的使用场景 : 输入参数是简单类型，返回值也是简单类型

// 对数器打表找规律的过程
// 1) 可以用最暴力的实现求入参不大情况下的答案，往往只需要最基本的递归能力
// 2) 打印入参不大情况下的答案，然后观察规律
// 3) 把规律变成代码，就是最优解了

// 有装下8个苹果的袋子、装下6个苹果的袋子，一定要保证买苹果时所有使用的袋子都装满
// 对于无法装满所有袋子的方案不予考虑，给定n个苹果，返回至少要多少个袋子
// 如果不存在每个袋子都装满的方案返回-1

#include <iostream>
#include <algorithm>

using namespace std;

int f(int rest);

int bags1(int apple)
{
    int ans = f(apple);
    return ans == INT_MAX ? -1 : ans;
}

// 当前还有rest个苹果，使用的每个袋子必须装满，返回至少几个袋子
int f(int rest)
{
    if (rest < 0)
    {
        return INT_MAX;
    }
    if (rest == 0)
    {
        return 0;
    }
    // 使用8规格的袋子，剩余的苹果还需要几个袋子，有可能返回无效解
    int p1 = f(rest - 8);
    // 使用6规格的袋子，剩余的苹果还需要几个袋子，有可能返回无效解
    int p2 = f(rest - 6);
    p1 += p1 != INT_MAX ? 1 : 0;
    p2 += p2 != INT_MAX ? 1 : 0;
    return min(p1, p2);
}

int bags2(int apple)
{
    if ((apple & 1) != 0)
    {
        return -1;
    }
    if (apple < 18)
    {
        if (apple == 0)
        {
            return 0;
        }
        if (apple == 6 || apple == 8)
        {
            return 1;
        }
        if (apple == 12 || apple == 14 || apple == 16)
        {
            return 2;
        }
        return -1;
    }
    return (apple - 18) / 8 + 3;
}

int main()
{
    for (int apple = 0; apple < 100; apple++)
    {
        cout << apple << " : " << bags1(apple) << endl;
    }
    return 0;
}