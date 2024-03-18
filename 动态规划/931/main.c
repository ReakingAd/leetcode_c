/**
 * 931. 下降路径最小和
 *
 * 给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。
 * 下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所
 * 选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。具体来说，位置 (row, col)
 * 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1) 。
 * 示例 1：
 *  输入：matrix = [[2,1,3],[6,5,4],[7,8,9]]
    输出：13
    解释：如图所示，为和最小的两条下降路径
   示例 2：
    输入：matrix = [[-19,57],[-40,-5]]
    输出：-59
    解释：如图所示，为和最小的下降路径
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
//    int dp[matrixSize][matrixColSize[0]];
//    int result = 2e9;
//    for(int i=0;i<matrixSize;i++)
//    {
//        for(int j=0;j<matrixColSize[i];j++)
//        {
//            // 第一行
//            if(0 == i)
//            {
//                dp[i][j] = matrix[i][j];
//            }
//            // 第一列
//            else if(0 == j)
//            {
//                dp[i][j] = fmin(dp[i-1][j], dp[i-1][j+1]) + matrix[i][j];
//            }
//            // 最后一列
//            else if(matrixColSize[0] - 1 == j)
//            {
//                dp[i][j] = fmin(dp[i-1][j-1], dp[i-1][j]) + matrix[i][j];
//            }
//            // 其他的一般情况
//            else
//            {
//                dp[i][j] = fmin(
//                        fmin(dp[i-1][j-1], dp[i-1][j]),
//                        dp[i-1][j+1]
//                        )  + matrix[i][j];
//            }
//            // 最后一行。在最后一行中选出最小值
//            if(matrixSize-1 == i)
//            {
//                result = fmin(result, dp[i][j]);
//            }
//        }
//    }
//    return result;
//}
int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
    int dp_odd[matrixColSize[0]]; // 备份奇数行
    int dp_even[matrixColSize[0]]; // 备份偶数行
    int result = INT_MAX;
    for(int i=0;i<matrixSize;i++)
    {
        for(int j=0;j<matrixColSize[i];j++)
        {
            // 第一行
            if(0 == i)
            {
                dp_even[j] = matrix[i][j];
            }
                // 第一列
            else if(0 == j)
            {
                if(i % 2 == 0)
                {
                    dp_even[j] = fmin(dp_odd[j], dp_odd[j+1]) + matrix[i][j];
                }
                else
                {
                    dp_odd[j] = fmin(dp_even[j], dp_even[j+1]) + matrix[i][j];
                }
            }
                // 最后一列
            else if(matrixColSize[0] - 1 == j)
            {
                if(i % 2 == 0)
                {
                    dp_even[j] = fmin(dp_odd[j], dp_odd[j-1]) + matrix[i][j];
                }
                else
                {
                    dp_odd[j] = fmin(dp_even[j], dp_even[j-1]) + matrix[i][j];
                }
            }
                // 其他的一般情况
            else
            {
                if(i % 2 == 0)
                {
                    dp_even[j] = fmin(
                            fmin(dp_odd[j-1], dp_odd[j]),
                            dp_odd[j+1]
                    )  + matrix[i][j];
                }
                else
                {
                    dp_odd[j] = fmin(
                            fmin(dp_even[j-1], dp_even[j]),
                            dp_even[j+1]
                    )  + matrix[i][j];
                }
            }
            // 最后一行。在最后一行中选出最小值
            if(matrixSize-1 == i)
            {
                if(i % 2 == 0)
                {
                    result = fmin(result, dp_even[j]);
                }
                else
                {
                    result = fmin(result, dp_odd[j]);
                }

            }
        }
    }
    return result;
}
int main() {
//    int matrixSize = 3;
//    int matrixColSize[3] = {3,3,3};
    int matrixSize = 2;
    int matrixColSize[2] = {2, 2};
    int **matrix = (int **)malloc(sizeof(int *) * matrixSize);
    for(int i=0;i<matrixSize;i++)
    {
        for(int j=0;j<matrixColSize[i];j++)
        {
            matrix[i] = (int *)malloc(sizeof(int) * matrixColSize[i]);
        }
    }
//    matrix[0][0] = 2; matrix[0][1] = 1; matrix[0][2] = 3;
//    matrix[1][0] = 6; matrix[1][1] = 5; matrix[1][2] = 4;
//    matrix[2][0] = 7; matrix[2][1] = 8; matrix[2][2] = 9;

    matrix[0][0] = -19; matrix[0][1] = 57;
    matrix[1][0] = -40; matrix[1][1] = -5;
    int result = minFallingPathSum(matrix, matrixSize, matrixColSize);
    printf("result=%3d", result);
    return 0;
}
