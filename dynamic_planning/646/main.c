/**
 * 646. 最长数对链
 *
 * 给你一个由 n 个数对组成的数对数组 pairs ，其中 pairs[i] = [lefti, righti] 且 lefti < righti 。
 * 现在，我们定义一种 跟随 关系，当且仅当 b < c 时，数对 p2 = [c, d] 才可以跟在 p1 = [a, b] 后面。我们用这种形式来构造 数对链 。
 * 找出并返回能够形成的 最长数对链的长度 。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
    示例 1：
        输入：pairs = [[1,2], [2,3], [3,4]]
        输出：2
        解释：最长的数对链是 [1,2] -> [3,4] 。

    示例 2：
        输入：pairs = [[1,2],[7,8],[4,5]]
        输出：3
        解释：最长的数对链是 [1,2] -> [4,5] -> [7,8] 。
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static inline int compare(const void* a, const void* b)
{
    return (*(int **)a)[0] - (*(int **)b)[0];
}
/**
 * 方法一、动态规划
 * 先排序，再dp
 */
int findLongestChain_dp(int** pairs, int pairsSize, int* pairsColSize) {
    qsort(pairs, pairsSize, sizeof(pairs[0]), compare);
    int dp[pairsSize];
    for(int i=0;i<pairsSize;i++) dp[i] = 1;
    for(int i=1;i<pairsSize;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(pairs[j][1] < pairs[i][0])
            {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[pairsSize-1];
}
int main() {
    int pairsSize = 3;
    int pairsColSize[3] = {2,2,2};
    int **pairs = (int **)malloc(sizeof(int *) * pairsSize);
    for(int i=0;i<pairsSize;i++)
    {
        pairs[i] = (int *)malloc(sizeof(int) * pairsColSize[i]);
    }
    pairs[0][0] = 1; pairs[0][1] = 2;
    pairs[1][0] = 7; pairs[1][1] = 8;
    pairs[2][0] = 4; pairs[2][1] = 5;
//    for(int i=0;i<3;i++)
//    {
//        for(int j=0;j<2;j++)
//        {
//            printf("%3d", pairs[i][j]);
//        }
//        putchar('\n');
//    }

    int ans = findLongestChain(pairs, pairsSize, pairsColSize);
    printf("ans=%3d\n", ans);
    return 0;
}
