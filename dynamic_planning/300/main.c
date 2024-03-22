/**
 * 300. 最长递增子序列
 *
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
 * 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列
    示例 1：
        输入：nums = [10,9,2,5,3,7,101,18]
        输出：4
        解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

    示例 2：
        输入：nums = [0,1,0,3,2,3]
        输出：4
    示例 3：
        输入：nums = [7,7,7,7,7,7,7]
        输出：1
 */
#include <stdio.h>
#include <limits.h>
#include <math.h>
/**
 *  ----------------------------------------------------------------------------------
 *  ****第一版错误的思路****。 测试用例 [4,10,4,3,8,9] 通不过
 *  dp[i] 存放子数组[0,i]的最长严格递增子序列的长度
 *  1) 遍历找比nums[i]小，且dp值最大的那个，记为dp[k] = M, 那么dp[i] = dp[k] + 1;
 *  2) 如果遍历完，也没找到比nums[i]小的，那么dp[i] = dp[i-1]
 *  -----------------------------------------------------------------------------------
 *  【错误分析】: 上述思路中1)中，遍历得到的dp[k] = X,并不一定与nums[i]能继续组成严格递增子序列。所以 dp[i] = dp[k] + 1 也就不成立。
 *  因此，能保持这个 加1 的递推关系，dp[i]的定义就要修改一下：
 *
 *  dp[i]存放的是 以nums[i]为结尾且是原数组的严格递增子序列，最长的长度。
 *  递推关系：
 *    1) 遍历 nums[0] ~ nums[i-1], 在所有 < nums[i] 的值中找出最大的 dp[k] = M 则dp[i] = dp[k] + 1
 *    2) 如果 nums[0] ~ nums[i-1] 中所有值都 >=nums[i], 则dp[i] = 1;
 *  最后取dp[]数组的最大值就是题解。
 *
 */
int lengthOfLIS(int* nums, int numsSize) {
    int dp[numsSize];
    dp[0] = 1; // 第一个元素的最长严格递增子序列就是自身，长度是1
    for(int i=1;i<numsSize;i++)
    {
        int temp_index = -1; // nums数组下标缓存变量。用于寻找之前的最大dp
        int temp_dp = INT_MIN;// dp值缓存变量。用于寻找之前的最大dp
        for(int j=0;j<i;j++)
        {
            if(nums[j] < nums[i] && dp[j] > temp_dp) // nums[i] 能继续组成严格递增子序列
            {
                temp_index = j;
                temp_dp = dp[j];
            }
        }
        // 如果没找到比nums[i]小的。说明nums[i]不能参与构成最长严格递增子序列
        if(-1 == temp_index)
        {
            dp[i] = 1;
        }
        else
        {
            dp[i] = dp[temp_index] + 1;
        }
    }
    int ans = INT_MIN;
    for(int i=0;i<numsSize;i++)
    {
        ans = fmax(ans, dp[i]);
    }
    return ans;
}
int main() {
//    int nums[8] = {10,9,2,5,3,7,101,18};
    int nums[9] = {1,3,6,7,9,4,10,5,6};
    int ans = lengthOfLIS(nums, 9);
    printf("ans=%3d\n", ans);
    return 0;
}
