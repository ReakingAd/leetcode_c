/**
 * 120. 三角形最小路径和
 * 给定一个三角形 triangle ，找出自顶向下的最小路径和。
 * 每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
 * 也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
 * 示例 1：
    输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    输出：11
    解释：如下面简图所示：
       2
      3 4
     6 5 7
    4 1 8 3
    自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

   示例 2：
    输入：triangle = [[-10]]
    输出：-10
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int print_matrix(int** triangle, int triangleSize, int* triangleColSize) {
    for(int i=0;i<triangleSize;i++)
    {
        for(int j=0;j<triangleColSize[i];j++)
        {
            printf("%3d", triangle[i][j]);
        }
        putchar('\n');
    }
}
int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    int result = 2e9;
    int dp[triangleSize][triangleColSize[triangleSize-1]];
    for(int i=0;i<triangleSize;i++)
    {
        for(int j=0;j<triangleColSize[i];j++)
        {
            if(0 ==i && 0 == j) dp[i][j] = triangle[i][j];
            else if(0 == j)
            {
                dp[i][j] = dp[i-1][j] + triangle[i][j];
            }
            else if(triangleColSize[i]-1 == j)
            {
                dp[i][j] = dp[i-1][j-1] + triangle[i][j];
            }
            else
            {
                dp[i][j] = fmin(dp[i-1][j-1], dp[i-1][j]) + triangle[i][j];
            }
            // 取最后一行中最小值
            if(triangleSize-1 == i)
            {
                result = fmin(dp[i][j], result);
            }
        }
    }
    return result;
}

// TODO: 调试。结果不对
//int minimumTotal_ERROR(int** triangle, int triangleSize, int* triangleColSize) {
//    printf("算法实现的不对，优化空间复杂度的过程错误。感觉用一个一维数组不能完成对有用的历史计算结果的备份。")
//    int result = 2e9;
////    int dp[triangleSize][triangleColSize[triangleSize-1]];
//    int dp[triangleColSize[triangleSize-1]];
//    for(int i=0;i<triangleSize;i++)
//    {
//        for(int j=0;j<triangleColSize[i];j++)
//        {
//            if(0 == i && 0 == j)
//            {
//                dp[j] = triangle[i][j];
//            }
//            else if(0 == j)
//            {
//                dp[j] = dp[j] + triangle[i][j];
//            }
//            else if(triangleColSize[i]-1 == j)
//            {
//                dp[j] = dp[j-1] + triangle[i][j];
//            }
//            else
//            {
//                dp[j] = fmin(dp[j-1], dp[j]) + triangle[i][j];
//            }
////            // 取最后一行中最小值
//            if(triangleSize-1 == i)
//            {
//                result = fmin(dp[j], result);
//            }
//        }
//    }
//    return result;
//}
int main() {
    int triangleSize = 4; // 4行
    int triangleColSize[] = {1,2,3,4}; // 第i行含的元素个数
    int **triangle = (int **)malloc(triangleSize * sizeof(int *));
    for(int i=0;i<triangleSize;i++)
    {
        for(int j=0;j<triangleColSize[i];j++)
        {
            triangle[i] = (int *)malloc(sizeof(int));
        }
    }
    triangle[0][0] = 2;
    triangle[1][0] = 3; triangle[1][1] = 4;
    triangle[2][0] = 6; triangle[2][1] = 5; triangle[2][2] = 7;
    triangle[3][0] = 4; triangle[3][1] = 1; triangle[3][2] = 8; triangle[3][3] = 3;
//    print_matrix(triangle, triangleSize, triangleColSize);
    int result = minimumTotal(triangle, triangleSize, triangleColSize);
    printf("result=%d", result);
    return 0;
}
