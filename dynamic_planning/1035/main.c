/**
 * 1035. 不相交的线
 * 在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。
    现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足：

     nums1[i] == nums2[j]
    且绘制的直线不与任何其他连线（非水平线）相交。
    请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

    以这种方法绘制线条，并返回可以绘制的最大连线数。
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
/**
 * 题目与【1143. 最长公共子序列】是一个意思，但是只能感觉出像，并不知道咋证明就是一样的。
 * 假设已经用最优解连上了线，这些线的起点依次组成一个数组a，这些线的终点依次组成数组b。可是
 * 直到数组a是nums1的子序列。数组b是nums2的子序列。a，b每个位置上的元素又相等。那么a、b
 * 就是nums1，nums2的最长公共子序列。
 *
 * dp定义、递推完全同 【1143. 最长公共子序列】，略
 */
int maxUncrossedLines(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int ans = INT_MIN;
    int dp[nums2Size+1][nums1Size+1];
    memset(dp, 0, sizeof(dp));
    for(int i=1;i<nums1Size+1;i++)
    {
        for(int j=1;j<nums2Size+1;j++)
        {
            int cur_num1 = nums1[i-1];
            int cur_num2 = nums2[j-1];
            if(cur_num1 == cur_num2)
            {
                dp[i][j] = dp[i-1][j-1] + 1;
                ans = fmax(ans, dp[i][j]);
            }
            else
            {
                dp[i][j] = fmax(dp[i-1][j], dp[i][j-1]);
                ans = fmax(ans, dp[i][j]);
            }
        }
    }
    for(int i=0;i<nums1Size+1;i++)
    {
        for(int j=0;j<nums2Size+1;j++)
        {
            printf("%3d", dp[i][j]);
        }
        putchar('\n');
    }
    return ans;
}
int main() {
//    输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
//    输出：3
    int nums1Size = 5;
    int nums1[nums1Size];
    nums1[0] = 2; nums1[1] = 5; nums1[2] = 1; nums1[3] = 2; nums1[4] = 5;
    int nums2Size = 5;
    int nums2[nums1Size];
    nums2[0] = 10; nums2[1] = 5; nums2[2] = 2; nums2[3] = 1; nums2[4] = 5; nums2[5] = 2;
    int ans = maxUncrossedLines(nums1, nums1Size, nums2, nums2Size);
    printf("ans=%d\n", ans);
    return 0;
}
