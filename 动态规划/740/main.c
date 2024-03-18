/**
* 740. 删除并获得点数
 * 给你一个整数数组 nums ，你可以对它进行一些操作。每次操作中，
 * 选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，
 * 你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
 * 开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
示例 1：

    输入：nums = [3,4,2]
    输出：6
    解释：
    删除 4 获得 4 个点数，因此 3 也被删除。
    之后，删除 2 获得 2 个点数。总共获得 6 个点数。
示例 2：
    输入：nums = [2,2,3,3,3,4]
    输出：9
    解释：
    删除 3 获得 3 个点数，接着要删除两个 2 和 4 。
    之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
    总共获得 9 个点数。
*/
#include <stdio.h>
#include <math.h>
/**
 * 【分析】
 * 以[2,2,3,3,3,4]为例。数据有重复项，且根据题意，数组也是无序的。没有一个好的
 * 遍历的方式。
 * 题中给出，取值的限制条件是数值不能挨着。因此构建一个新数组，以数值作为新数组的
 * 下标，于是限制条件就转变成了【下标不能挨着】。这就靠近了动态规划的题型：从下标0
 * 向后遍历，计算出dp数组，那么dp数组的最后两项的最大值就是题解。
 * 想到这里，再考虑 [2,2,3,3,3,4] 出现重复值的问题。出现的两次2，可以累加到下标
 * 是2的数值上，构成下标2的新的权重值。
 */
int deleteAndEarn(int* nums, int numsSize) {
    int arr[10000 + 1] = {0}; // 初始化所有元素为0
    int max=0; // 新数组的最大下标
    // 元素值做下标，该元素总收益（即元素值*元素个数）作为新数组的值
    for(int i=0;i<numsSize;i++)
    {
        arr[nums[i]] += nums[i];
        max = nums[i] > max ? nums[i] : max;
    }
    // [0, 0, 4, 9, 4]
    // 下面就变成了常规的动态规划 - 斐波那契数列类型的题目
    int dp[max+1];
    for(int i=0;i<=max;i++)
    {
        if(i<3) dp[i] = arr[i];
        else dp[i] = fmax(dp[i-2], dp[i-3]) + arr[i];
    }
    return fmax(dp[max], dp[max-1]);
}
int main()
{
//    int nums[6] = {2, 2, 3, 3, 3, 4};
    int nums[3] = {3, 4, 2};
    int result = deleteAndEarn(nums, 3);
    printf("%d", result);
    return 0;
}