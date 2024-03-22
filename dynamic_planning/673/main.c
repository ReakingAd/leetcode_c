/**
 * 673. 最长递增子序列的个数
 * 给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
 * 注意 这个数列必须是 严格 递增的。
    示例 1:
        输入: [1,3,5,4,7]
        输出: 2
        解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。

    示例 2:
        输入: [2,2,2,2,2]
        输出: 5
        解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
/**
 * dp[i]的定义同第300题：以nums[i]为结尾的子序列中，最长的那个递增子序列的长度
 * 递推关系：
 * 1) 遍历 nums[0] ~ nums[i-1],在所有比nums[i]值小的下标中，找出最大的那个dp[k]，则dp[i] = dp[k] + 1
 * 2) 遍历 nums[0] ~ nums[i-1], 如果所有元素都比 nums[i]大，则dp[i] = 1
 *
 * 同时，维护一个count[]数组， count[i]记录的是以nums[i]为结尾的最长递增子序列个数。
 * 递推关系，设dp[0] ~ dp[i-1]中， 最大值为dp[K] = M 。 count[i] = dp中所有值为M的下标x，对应的count[x]的和
 */
int findNumberOfLIS(int* nums, int numsSize) {
    int dp[numsSize]; // 存储以nums[i]为结尾的最长递增子序列的长度
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    int count[numsSize]; // 存储以nums[i]为结尾的最长递增子序列的个数
    memset(count, 0, sizeof(count));
    count[0] = 1;
    int MAX = dp[0];
    int MAX_len = 1;
    for(int i=1;i<numsSize;i++) {
        int temp_dp = -1; // 缓存dp值，用来寻找所有比nums[i]值小的中，dp值最大的那个
        int temp_dp_count = 0; // 缓存最大dp值temp_dp的个数
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) // 可以继续使用nums[i]构成严格递增子序列
            {
                // 新发现一个最值，则更新缓存temp_dp，即个数 temp_dp_count
                if(dp[j] > temp_dp)
                {
                    temp_dp = dp[j];
                    temp_dp_count = count[j];
                }
                // 发现一个出现过的最值。个数 temp_dp_count 累加
                else if(dp[j] == temp_dp)
                {
                    temp_dp_count += count[j];
                }
            }
        }
        // 如果没有找到比nums[i]的值。也就是说nums[i]为结尾的最长严格递增子序列是自身。
        if(-1 == temp_dp)
        {
            dp[i] = 1;
            count[i] = 1;
        }
        // 如果nums[i]可以与前面的元素继续构成更长的严格递增子序列。那么记录当前的dp值，及个数
        else{
            dp[i] = temp_dp + 1;
            count[i] = temp_dp_count;
        }
        // 找到最大的那个 dp 值。并把所有最大dp值所对应的i值，所对应的count值累加在一起。
        if(dp[i] > MAX)
        {
            MAX = dp[i];
            MAX_len = count[i];
        }
        else if(dp[i] == MAX)
        {
            MAX_len += count[i];
        }
    }
//    for(int i=0;i<numsSize;i++)
//    {
//        printf("%3d", nums[i]);
//    }
//    putchar('\n');
//    for(int i=0;i<numsSize;i++)
//    {
//        printf("%3d", dp[i]);
//    }
//    putchar('\n');
//    for(int i=0;i<numsSize;i++)
//    {
//        printf("%3d", count[i]);
//    }
//    putchar('\n');
    return MAX_len;
}
int main() {
    int nums[5] = {1,3,5,4,7};
//    int nums[5] = {2,2,2,2,2};
//    int nums[8] = {1,2,4,3,5,4,7,2};
//    int nums[5] = {1,3,5,4,7};
    int ans = findNumberOfLIS(nums, 5);
    printf("ans=%d\n", ans);
    return 0;
}
