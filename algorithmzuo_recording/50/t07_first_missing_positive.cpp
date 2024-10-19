// 缺失的第一个正数
// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
// 测试链接 : https://leetcode.cn/problems/first-missing-positive/

class Solution
{
public:
    int firstMissingPositive(vector<int> &arr)
    {
        // l的左边，都是做到i位置上放着的值为i+1
        // 永远盯着l位置的数字看，看能不能扩充(l++)
        int l = 0;
        // [r....]垃圾区
        // 最好的状况下，认为l~r是可以收集全的，每个数字收集1个，不能有垃圾
        // 有垃圾呢？预期就会变差(r--)
        int r = arr.size();
        while (l < r)
        {
            if (arr[l] == l + 1)
            {
                l++;
            }
            // arr[l] <= l || arr[l] > r --> 垃圾区
            // arr[arr[l] - 1] == arr[l] --> 出现重复数字 --> 垃圾区
            // l 1 2 3 4 .. r
            // 5 2 4 3 5
            else if (arr[l] <= l || arr[l] > r || arr[arr[l] - 1] == arr[l])
            {
                swap(arr[l], arr[--r]);
            }
            else
            { // 在l...r范围内，所以将数转移到正确位置
                swap(arr[l], arr[arr[l] - 1]);
            }
        }
        return l + 1;
    }
};