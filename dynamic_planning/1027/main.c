/**
 * 1027. 最长等差数列
 *
 * 给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。
 * 回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，
 * 且 0 <= i1 < i2 < ... < ik <= nums.length - 1。
 * 并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
    示例 1：
        输入：nums = [3,6,9,12]
        输出：4
        解释：
        整个数组是公差为 3 的等差数列。

    示例 2：
        输入：nums = [9,4,7,2,10]
        输出：3
        解释：
        最长的等差子序列是 [4,7,10]。
    示例 3：
        输入：nums = [20,1,15,3,10,5,8]
        输出：4
        解释：
        最长的等差子序列是 [20,15,10,5]。

    提示：
        2 <= nums.length <= 1000
        0 <= nums[i] <= 500
 */
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
/**
 * 差的范围是 [-500, 500], 所以使用num+500作为哈希函数，避免出现负下标。所以最大的下标可能为 500 + 500 = 1000。数组容量为1000+1=1001
 * dp[x][y] 行数x，对应差值。列数y对应 最长等差子序列的最后一个元素
 * 递推关系：
 *     差 diff = nums[i] - nums[j], 第diff行，第 nums[j] 列是否有值
 *     1) 如果有值，则 dp[diff][nums[i]] = 值 + 1
 *     2) 如果无知，则 dp[diff][nums[i]] = 2
 *
 * 在考虑等差为0的数列。
 * 当公差不为0时，dp的行（公差）列（最后一个元素）可以唯一表示一个子序列。但是当公差为0时，就不行了，双内for循环内会出现重复计数的问题。
 * 因此可使用第0行，单独为nums的每个元素进行累加记录出现的次数，并且在之前定的for循环内， 遇到diff=0的情况就continue，
 * 不做任何事情。
 *
 * TODO: 优化。时间复杂度O(n^2),空间复杂度O(n^2)都很差。比较一下官方题解的方法。
 */
int hash(int num)
{
    return num + 500;
}
int longestArithSeqLength(int* nums, int numsSize) {
    int ans = INT_MIN;
    int (*dp)[1001] = malloc(sizeof(int[1001]) * 1001);
    for(int i=0;i<1001;i++)
    {
        for(int j=0;j<1001;j++)
        {
            dp[i][j] = 0;
        }
    }
    for(int i=0;i<numsSize;i++)
    {
        dp[0][hash(nums[i])] = dp[0][hash(nums[i])] + 1;
        ans = fmax(ans, dp[0][hash(nums[i])]);
        for(int j=0;j<i;j++)
        {
            int diff = nums[i] - nums[j];
            if(0 == diff)
            {
                continue;
            }
            if(0 != dp[hash(diff)][hash(nums[j])])
            {
                dp[hash(diff)][hash(nums[i])] = dp[hash(diff)][hash(nums[j])] + 1;
            }
            else
            {
                dp[hash(diff)][hash(nums[i])] = 2;
            }
            ans = fmax(ans, dp[hash(diff)][hash(nums[i])]);
        }
    }
    free(dp);
    return ans;
}
int main() {
    int numsSize = 60;
//    int nums[numsSize];
    int nums[60] = {
            12,28,13,6,34,36,53,24,29,2,
            23,0,22,25,53,34,23,50,35,43,
            53,11,48,56,44,53,31,6,31,57,
            46,6,17,42,48,28,5,24,0,14,
            43,12,21,6,30,37,16,56,19,45,
            51,10,22,38,39,23,8,29,60,18
    };
//    nums[0] = 20; nums[1] = 1; nums[2] = 15; nums[3] = 3; nums[4] = 10;
//    nums[5] = 5; nums[6] = 8;
    int ans = longestArithSeqLength(nums, numsSize);
    printf("ans=%d", ans);
    return 0;
}
