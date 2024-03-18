/**
 * 221. 最大正方形
 * 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。
 * 示例 1：
 *   输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
     输出：4
   示例 2：
     输入：matrix = [["0"]]
     输出：0
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * f(i)(j) 是以(i,j)格子作为右下角的最大正方形的边长。
 * 递推关系： f(i,j) = min[ f(i-1,j-1) f(i-1,j) f(i,j-1) ] + 1
 */
//int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
//    int num = INT_MIN;
//    int dp[matrixSize][matrixColSize[0]];
//    for(int i=0;i<matrixSize;i++)
//    {
//        for(int j=0;j<matrixColSize[i];j++)
//        {
//            // 第一行
//            if(0 == i || 0 == j)
//            {
//                dp[i][j] = matrix[i][j] - '0';
//            }
//            // 其他格子
//            else
//            {
//                if(matrix[i][j] - '0' == 0) dp[i][j] = 0;
//                else dp[i][j] = fmin( fmin(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1] )  + 1;
//            }
//            num = fmax(num, dp[i][j]);
//        }
//    }
//    return num * num;
//}
int maximalSquare(char** matrix, int matrixSize, int* matrixColSize) {
    int num = INT_MIN;
//    int dp[matrixSize][matrixColSize[0]];
    int dp[matrixColSize[0]]; // 备份当前行，用来计算下一行的值
    int prev; // 备份当前格子的值，用来计算下一行的值
    for(int i=0;i<matrixSize;i++)
    {
        for(int j=0;j<matrixColSize[i];j++)
        {
            // 第一行
            if(0 == i || 0 == j)
            {
                dp[j] = matrix[i][j] - '0';
            }
                // 其他格子
            else
            {
                if(matrix[i][j] - '0' == 0)
                {
                    dp[j] = 0;
                }
                else
                {
                    dp[j] = fmin( fmin(dp[j-1], dp[j]), prev )  + 1;
                }
            }
            prev = dp[j];
            dp[j]
            num = fmax(num, dp[j]);
        }
    }
    return num * num;
}
int main() {
    int matrixSize = 4;
    int matrixColSize[4] = {5,5,5,5};
    char **matrix = (char **)malloc(sizeof(char *) * matrixSize);
    for(int i=0;i<matrixSize;i++)
    {
        matrix[i] = (char *)malloc(sizeof(char) * matrixColSize[i]);
    }
    matrix[0][0] = '1'; matrix[0][1] = '0'; matrix[0][2] = '1'; matrix[0][3] = '0'; matrix[0][4] = '0';
    matrix[1][0] = '1'; matrix[1][1] = '0'; matrix[1][2] = '1'; matrix[1][3] = '1'; matrix[1][4] = '1';
    matrix[2][0] = '1'; matrix[2][1] = '1'; matrix[2][2] = '1'; matrix[2][3] = '1'; matrix[2][4] = '1';
    matrix[3][0] = '1'; matrix[3][1] = '0'; matrix[3][2] = '0'; matrix[3][3] = '1'; matrix[3][4] = '0';
    int result = maximalSquare(matrix, matrixSize, matrixColSize);
    printf("result=%d\n", result);
    return 0;
}
