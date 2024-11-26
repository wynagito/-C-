// AVL实现普通有序表，数据加强的测试
// 这个文件课上没有讲，测试数据加强了，而且有强制在线的要求
// 基本功能要求都是不变的，可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P6136

#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

const int MAXN = 2000001;

int cnt = 0;
int head = 0;
int key[MAXN];
int height[MAXN];
int ls[MAXN];
int rs[MAXN];
int key_count[MAXN];
int size[MAXN];

void up(int i)
{
    size[i] = size[ls[i]] + size[rs[i]] + key_count[i];
    height[i] = max(height[ls[i]], height[rs[i]]) + 1;
}

int leftRotate(int i)
{
    int r = rs[i];
    rs[i] = ls[r];
    ls[r] = i;
    up(i);
    up(r);
    return r;
}

int rightRotate(int i)
{
    int l = ls[i];
    ls[i] = rs[l];
    rs[l] = i;
    up(i);
    up(l);
    return l;
}

int maintain(int i)
{
    int lh = height[ls[i]];
    int rh = height[rs[i]];
    if (lh - rh > 1)
    {
        if (height[ls[ls[i]]] >= height[rs[ls[i]]])
        {
            i = rightRotate(i);
        }
        else
        {
            ls[i] = leftRotate(ls[i]);
            i = rightRotate(i);
        }
    }
    else if (rh - lh > 1)
    {
        if (height[rs[rs[i]]] >= height[ls[rs[i]]])
        {
            i = leftRotate(i);
        }
        else
        {
            rs[i] = rightRotate(rs[i]);
            i = leftRotate(i);
        }
    }
    return i;
}

int add(int i, int num)
{
    if (i == 0)
    {
        key[++cnt] = num;
        key_count[cnt] = size[cnt] = height[cnt] = 1;
        return cnt;
    }
    if (key[i] == num)
    {
        key_count[i]++;
    }
    else if (key[i] > num)
    {
        ls[i] = add(ls[i], num);
    }
    else
    {
        rs[i] = add(rs[i], num);
    }
    up(i);
    return maintain(i);
}

void add(int num)
{
    head = add(head, num);
}

int getRank(int i, int num)
{
    if (i == 0)
    {
        return 0;
    }
    if (key[i] >= num)
    {
        return getRank(ls[i], num);
    }
    else
    {
        return size[ls[i]] + key_count[i] + getRank(rs[i], num);
    }
}

int getRank(int num)
{
    return getRank(head, num) + 1;
}

int removeMostLeft(int i, int mostLeft)
{
    if (i == mostLeft)
    {
        return rs[i];
    }
    else
    {
        ls[i] = removeMostLeft(ls[i], mostLeft);
        up(i);
        return maintain(i);
    }
}

int remove(int i, int num)
{
    if (key[i] < num)
    {
        rs[i] = remove(rs[i], num);
    }
    else if (key[i] > num)
    {
        ls[i] = remove(ls[i], num);
    }
    else
    {
        if (key_count[i] > 1)
        {
            key_count[i]--;
        }
        else
        {
            if (ls[i] == 0 && rs[i] == 0)
            {
                return 0;
            }
            else if (ls[i] != 0 && rs[i] == 0)
            {
                i = ls[i];
            }
            else if (ls[i] == 0 && rs[i] != 0)
            {
                i = rs[i];
            }
            else
            {
                int mostLeft = rs[i];
                while (ls[mostLeft] != 0)
                {
                    mostLeft = ls[mostLeft];
                }
                rs[i] = removeMostLeft(rs[i], mostLeft);
                ls[mostLeft] = ls[i];
                rs[mostLeft] = rs[i];
                i = mostLeft;
            }
        }
    }
    up(i);
    return maintain(i);
}

void remove(int num)
{
    if (getRank(num) != getRank(num + 1))
    {
        head = remove(head, num);
    }
}

int index(int i, int x)
{
    if (size[ls[i]] >= x)
    {
        return index(ls[i], x);
    }
    else if (size[ls[i]] + key_count[i] < x)
    {
        return index(rs[i], x - size[ls[i]] - key_count[i]);
    }
    return key[i];
}

int index(int x)
{
    return index(head, x);
}

int pre(int i, int num)
{
    if (i == 0)
    {
        return INT_MIN;
    }
    if (key[i] >= num)
    {
        return pre(ls[i], num);
    }
    else
    {
        return max(key[i], pre(rs[i], num));
    }
}

int pre(int num)
{
    return pre(head, num);
}

int post(int i, int num)
{
    if (i == 0)
    {
        return INT_MAX;
    }
    if (key[i] <= num)
    {
        return post(rs[i], num);
    }
    else
    {
        return min(key[i], post(ls[i], num));
    }
}

int post(int num)
{
    return post(head, num);
}

void clear()
{
    memset(key + 1, 0, cnt * sizeof(int));
    memset(height + 1, 0, cnt * sizeof(int));
    memset(ls + 1, 0, cnt * sizeof(int));
    memset(rs + 1, 0, cnt * sizeof(int));
    memset(key_count + 1, 0, cnt * sizeof(int));
    memset(size + 1, 0, cnt * sizeof(int));
    cnt = 0;
    head = 0;
}

int main()
{
    int n, m, lastAns = 0, ans = 0;
    cin >> n;
    cin >> m;
    for (int i = 1, num; i <= n; i++)
    {
        cin >> num;
        add(num);
    }
    for (int i = 1, op, x; i <= m; i++)
    {
        cin >> op >> x;
        x ^= lastAns;
        if (op == 1)
        {
            add(x);
        }
        else if (op == 2)
        {
            remove(x);
        }
        else if (op == 3)
        {
            lastAns = getRank(x);
            ans ^= lastAns;
        }
        else if (op == 4)
        {
            lastAns = index(x);
            ans ^= lastAns;
        }
        else if (op == 5)
        {
            lastAns = pre(x);
            ans ^= lastAns;
        }
        else
        {
            lastAns = post(x);
            ans ^= lastAns;
        }
    }
    cout << ans << endl;
    clear();
    return 0;
}