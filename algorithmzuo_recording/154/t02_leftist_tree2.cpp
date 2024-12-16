// 左偏树删除任意编号的节点
// 1，建立树上父节点信息up数组，树上真实父节点信息up != 并查集的路径信息father
// 2，假设删除节点为i，整棵树的头假设为h，节点i的左右树合并，形成的树假设为s
// 3，假设节点i的树上父节点为f，去掉节点i，节点f和节点s直接连在一起
// 4，从s节点往上，更新节点的dist值，如果发现，左儿子dist < 右儿子dist，就交换左右树
// 5，需要保证每个节点的up、left、right、dist、father信息更新正确

// 核心在于第4点，保证左偏树的性质，修改节点总数为O(log n)

// 左偏树模版题2，数据量增强
// 依次给定n个非负数字，表示有n个小根堆，每个堆只有一个数
// 实现如下两种操作，操作一共调用m次
// M x y : 第x个数字所在的堆和第y个数字所在的堆合并
//         如果两个数字已经在一个堆或者某个数字已经删除，不进行合并
// K x   : 打印第x个数字所在堆的最小值，并且在堆里删掉这个最小值
//         如果第x个数字已经被删除，也就是找不到所在的堆，打印0
//         若有多个最小值，优先删除编号小的
// 1 <= n <= 10^6
// 1 <= m <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P2713

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000001;
int n, m;
int num[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];

void prepare()
{
    dist[0] = -1;
    for (int i = 1; i <= n; i++)
    {
        ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i)
{
    fa[i] = fa[i] == i ? i : find(fa[i]);
    return fa[i];
}

int merge(int i, int j)
{
    if (i == 0 || j == 0)
    {
        return i + j;
    }
    if (num[i] > num[j] || (num[i] == num[j] && i > j))
    {
        int tmp = i;
        i = j;
        j = tmp;
    }
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]])
    {
        int tmp = ls[i];
        ls[i] = rs[i];
        rs[i] = tmp;
    }
    dist[i] = dist[rs[i]] + 1;
    fa[ls[i]] = fa[rs[i]] = i;
    return i;
}

int pop(int i)
{
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    fa[i] = merge(ls[i], rs[i]);
    ls[i] = rs[i] = dist[i] = 0;
    return fa[i];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    prepare();
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        string op;
        cin >> op;
        if (op == "M")
        {
            int x, y;
            cin >> x >> y;
            if (num[x] != -1 && num[y] != -1)
            {
                int l = find(x);
                int r = find(y);
                if (l != r)
                {
                    merge(l, r);
                }
            }
        }
        else
        {
            int x;
            cin >> x;
            if (num[x] == -1)
            {
                cout << 0 << endl;
            }
            else
            {
                int ans = find(x);
                cout << num[ans] << endl;
                pop(ans);
                num[ans] = -1;
            }
        }
    }
    return 0;
}