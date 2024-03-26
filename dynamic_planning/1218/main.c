/**
 * 1218. 最长定差子序列
 * 给你一个整数数组 arr 和一个整数 difference，请你找出并返回 arr 中最长等差子序列的长度，该子序列中相邻元素之间的差等于 difference 。
 * 子序列 是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从 arr 派生出来的序列。
    示例 1：
        输入：arr = [1,2,3,4], difference = 1
        输出：4
        解释：最长的等差子序列是 [1,2,3,4]。
    示例 2：
        输入：arr = [1,3,5,7], difference = 1
        输出：1
        解释：最长的等差子序列是任意单个元素。
    示例 3：
        输入：arr = [1,5,7,8,5,3,4,2,1], difference = -2
        输出：4
        解释：最长的等差子序列是 [7,5,3,1]。

    提示：
        1 <= arr.length <= 105
        -104 <= arr[i], difference <= 104
 */
#include <stdio.h>
#include <limits.h>
#include <math.h>
/**
 * 【dp】此方法双层for循环，测试用例超时。
 * dp[i]代表：以arr[i]为结尾的最长等差子序列的长度
 * 初始值：dp[i] = 1; 也就是默认最长等差子序列就是自己所组成的单元素子序列。
 * 递推关系：
 *      1) 遍历arr[i] ~ arr[i-1],找出所有比arr[i]大 difference 的下标，
 *          然后在这些下标中取dp最大的那个。赋值给dp[i] = dp[k] + 1;
 *      2) 遍历arr[i] ~ arr[i-1],如果没找到比arr[i]大 difference 的下标，则continue
 */
//int longestSubsequence(int* arr, int arrSize, int difference) {
//    int hash_table[40000] = {0};
//    int ans = INT_MIN;
//    int dp[arrSize];
//    for(int i=0;i<arrSize;i++) dp[i] = 1;
//    for(int i=1;i<arrSize;i++)
//    {
//        for(int j=0;j<i;j++)
//        {
//            if(arr[i] - arr[j] == difference)
//            {
//                dp[i] = fmax(dp[j]+1, dp[i]);
//            }
//            ans = fmax(ans, dp[i]);
//        }
//    }
//    for(int i=0;i<arrSize;i++)
//    {
//        printf("%3d", dp[i]);
//    }
//    return ans;
//}
/**
 * 双层循环的dp超时，时间复杂度是O(n^2)。可以优化的点在于，当计算dp[i]的值时，设A = arr[i]  B=A-difference
 * 那么只需要知道dp[B]就可以计算dp[A]。如果用一个哈希表存储上已经计算的dp[B]的值，那么内层for循环就可以不要了，
 * 代替他的是O(1)时间复杂度的哈希表查询。
 *
 * 本题中，已有提示 -10000 <= arr[i], difference <= 10000
 * 可知arr[i] - difference可能计算出的最小值为 -10000 - 10000 = -20000
 * 考虑使用数组来实现hash table，为了避免负下标的出现，哈希函数可以使用 num + 20000。数组的容量初步可尝试20000 + 20000 = 40000
 * 提交后发现可以通过测试用例。
 */
int longestSubsequence(int* arr, int arrSize, int difference) {
    int hash_table[40000] = {0};
    int ans = INT_MIN;
    for(int i=1;i<arrSize;i++)
    {
        hash_table[arr[i] + 20000] = hash_table[arr[i] - difference + 20000] + 1;
        ans = fmax(ans, hash_table[arr[i] + 20000]);
    }
    return ans;
}
int main() {
    int arrSize = 9;
    int arr[arrSize];
    arr[0] = 1; arr[1] = 5; arr[2] = 7; arr[3] = 8; arr[4] = 5;
    arr[5] = 3; arr[6] = 4; arr[7] = 2; arr[8] = 1;
    int difference = -2;
    int ans = longestSubsequence(arr, arrSize, difference);
    printf("ans=%d", ans);
    return 0;
}
