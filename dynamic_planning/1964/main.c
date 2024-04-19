/**
 * 1964. 找出到每个位置为止最长的有效障碍赛跑路线
 * 你打算构建一些障碍赛跑路线。给你一个 下标从 0 开始 的整数数组 obstacles ，数组长度为 n ，其中 obstacles[i] 表示第 i 个障碍的高度。
 * 对于每个介于 0 和 n - 1 之间（包含 0 和 n - 1）的下标  i ，在满足下述条件的前提下，请你找出 obstacles 能构成的最长障碍路线的长度：
    你可以选择下标介于 0 到 i 之间（包含 0 和 i）的任意个障碍。
    在这条路线中，必须包含第 i 个障碍。
    你必须按障碍在 obstacles 中的 出现顺序 布置这些障碍。
    除第一个障碍外，路线中每个障碍的高度都必须和前一个障碍 相同 或者 更高 。
    返回长度为 n 的答案数组 ans ，其中 ans[i] 是上面所述的下标 i 对应的最长障碍赛跑路线的长度。



    示例 1：
        输入：obstacles = [1,2,3,2]
        输出：[1,2,3,3]
        解释：每个位置的最长有效障碍路线是：
        - i = 0: [1], [1] 长度为 1
        - i = 1: [1,2], [1,2] 长度为 2
        - i = 2: [1,2,3], [1,2,3] 长度为 3
        - i = 3: [1,2,3,2], [1,2,2] 长度为 3
    示例 2：
        输入：obstacles = [2,2,1]
        输出：[1,2,1]
        解释：每个位置的最长有效障碍路线是：
        - i = 0: [2], [2] 长度为 1
        - i = 1: [2,2], [2,2] 长度为 2
        - i = 2: [2,2,1], [1] 长度为 1
    示例 3：
        输入：obstacles = [3,1,5,6,4,2]
        输出：[1,1,2,3,2,2]
        解释：每个位置的最长有效障碍路线是：
        - i = 0: [3], [3] 长度为 1
        - i = 1: [3,1], [1] 长度为 1
        - i = 2: [3,1,5], [3,5] 长度为 2, [1,5] 也是有效的障碍赛跑路线
        - i = 3: [3,1,5,6], [3,5,6] 长度为 3, [1,5,6] 也是有效的障碍赛跑路线
        - i = 4: [3,1,5,6,4], [3,4] 长度为 2, [1,4] 也是有效的障碍赛跑路线
        - i = 5: [3,1,5,6,4,2], [1,2] 长度为 2

 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 【注】leetcode给定义的参数returnSize是返回的结果数组的大小。并不是结果数组本身。
 *
 * 方法一、 常规dp， 时间复杂度O(n^2) 测试用例超时
 * dp 为题目要求的结果数组
 * 递推关系：
 *    遍历 obstacles[0] ~ obstacles[i-1], 找出所有 <= obstacles[i]的，并在他们中找出最大的 obstacles[j]。 dp[i] = obstacles[j] + 1
 */
int* longestObstacleCourseAtEachPosition_1(int* obstacles, int obstaclesSize, int* returnSize) {
    *returnSize = obstaclesSize;
    int *dp = (int*)malloc(sizeof(int) * obstaclesSize);
    for(int i=0;i<obstaclesSize;i++) dp[i] = 1;
    for(int i=1;i<obstaclesSize;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(obstacles[j] <= obstacles[i])
            {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }
    return dp;
}
int bi_search(int* arr, int size, int target)
{
    int left = 0;
    int right = size-1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(arr[mid] == target)
        {
            if(target < arr[mid+1]) return mid+1;
            left = mid + 1;
        }
//
        if(target < arr[mid])
        {
            if(mid > 0 && target >= arr[mid-1]) return mid;
            right = mid - 1;
        }
        else if(target > arr[mid])
        {
            if(target < arr[mid+1]) return mid+1;
            left = mid + 1;
        }
    }
    return mid;
}
/**
 * 方法二：贪心+二分， 时间复杂度o(nlogn)
 * 基本等同于题目： 300. 最长递增子序列
 * 维护两个数组：
 *      - 数组f[]用于贪心, f[i]存放长度为i的障碍路线，末端所能放的最小的值
 *      - 数组ans[]用于存放最终答案，ans[i]存放以当前obstacles[i]为末位的障碍的总长度。
 *
 * 遍历obstacles数组：
 *    1. 如果obstacles[i] >= f[]数组的末位，则直接追加到f[]的末位
 *    2. 如果obstacles[i] < f[]数组的末位，则使用二分查找这样一个位置k，k需要满足：
 *            f[k-1] <= obstacles[i] < f[k]
 *       然后用obstacles[i]取代f[k],完成对f[]数组的更新
 *
 *  上述步骤1,2是对f[]数组的维护。在每次对f[]做更新时，要同步更新ans[]数组，更新策略是：
 *  不管 obstacles[i]是插入末位（步骤1）还是插入f[]的中间（步骤2）,
 *     ans[i] = obstacles[i]所插入到的f[]的位置索引 + 1
 *
 *  【难点】：以前写的二分查找是找到等值的位置返回，找不到返回-1。此题要求等值的障碍也可以加入队伍，
 *  因此二分查找的if判断中，要对相邻像两个元素进行判断。
 *
 *  执行时间击败了5.88%的c语言用户 - -！
 */
int* longestObstacleCourseAtEachPosition(int* obstacles, int obstaclesSize, int* returnSize) {
    int *f = (int*)malloc(sizeof(int) * obstaclesSize);
    int len;
    f[0] = obstacles[0];
    len = 1;

    int *ans = (int*)malloc(sizeof(int) * obstaclesSize);
    int ans_len;
    ans[0] = 1;
    ans_len = 1;
    for(int i=1;i<obstaclesSize;i++)
    {
        if(obstacles[i] >= f[len-1])
        {
            f[len] = obstacles[i];
            len++;
            ans[ans_len] = len;
            ans_len++;
        }
        else
        {
            int pos = bi_search(f, len, obstacles[i]);
            ans[ans_len] = pos+1;
            ans_len++;
            printf("pos=%d\n", pos);
            f[pos] = obstacles[i];
        }
    }
    *returnSize = ans_len;
    puts("f::");
    for(int i=0;i<len;i++)
    {
        printf("%3d", f[i]);
    }
    putchar('\n');
    return ans;
}
int main() {
//    [3,1,5,6,4,2]
//    [1,2,3,2]
    int obstaclesSize = 10;
    int obstacles[obstaclesSize];
//    obstacles[0] = 3; obstacles[1] = 1; obstacles[2] = 5;
//    obstacles[3] = 6; obstacles[4] = 4; obstacles[5] = 2;
//    [5,1,5,5,1,3,4,5,1,4]
    obstacles[0] = 5; obstacles[1] = 2; obstacles[2] = 5; obstacles[3] = 4; obstacles[4] = 1;
    obstacles[5] = 1; obstacles[6] = 1; obstacles[7] = 5; obstacles[8] = 3; obstacles[9] = 1;

    int returnSize;
    int *ans = longestObstacleCourseAtEachPosition(obstacles, obstaclesSize, &returnSize);
    for(int i=0;i<returnSize;i++)
    {
        printf("%3d", ans[i]);
    }

//    bin_search() test
//    int obstaclesSize = 8;
//    int obstacles[obstaclesSize];
//    obstacles[0] = 0; obstacles[1] = 5; obstacles[2] = 13; obstacles[3] = 14;
//    obstacles[4] = 15; obstacles[5] = 16; obstacles[6] = 17; obstacles[7] = 18;
//    int pos = bi_search(obstacles, obstaclesSize, 8);
//    printf("pos=%d", pos);
    return 0;
}
