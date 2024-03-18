/**
 * 64. 最小路径和
 * 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 * 示例 1：
 *  输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
    输出：7
    解释：因为路径 1→3→1→1→1 的总和最小。
   示例 2：
    输入：grid = [[1,2,3],[4,5,6]]
    输出：12

 * TODO: 看看官方题解中，怎么定义二维数组的？minPathSum()外部定义二维数组好像不会体现在题解中...
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * 1 3 1
 * 1 5 1
 * 4 2 1
 */
int minPathSum(int** grid, int gridSize, int* gridColSize) {
//    int **dp = (int **) malloc(sizeof(int *) * gridSize);
//    for(int i=0;i<gridSize;i++)
//    {
//        dp[i] = (int *) malloc(sizeof(int) * gridColSize[i]);
//    }
    int m = gridSize;
    int n = gridColSize[0];
    int dp[m][n];
    for(int i=0;i<gridSize;i++)
    {
        for(int j=0;j<gridColSize[i];j++)
        {
            if(0 == i && 0 == j) dp[i][j] = grid[0][0];
            else if(0 == i) dp[i][j] = dp[i][j-1] + grid[i][j];
            else if(0 == j) dp[i][j] = dp[i-1][j] + grid[i][j];
            else dp[i][j] = fmin(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[gridSize-1][gridColSize[gridSize-1]-1];
}
//void printMatrix(int matrix[][]) {
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < 3; j++) {
//            printf("%d ", matrix[i][j]);
//        }
//        printf("\n");
//    }
//}
#define test 3;

int main() {

    int gridSize = 3;
    int gridColSize[3] = {3, 3, 3};
    int **grid = (int **) malloc(gridSize * sizeof(int *));
    for(int i=0;i<gridSize;i++)
    {
        grid[i] = (int *) malloc(gridColSize[i] * sizeof(int));
    }
    grid[0][0] = 1; grid[0][1] = 3; grid[0][2] = 1;
    grid[1][0] = 1; grid[1][1] = 5; grid[1][2] = 1;
    grid[2][0] = 4; grid[2][1] = 2; grid[2][2] = 1;

    int result = minPathSum(grid, gridSize, gridColSize);
    printf("%d", result);
//    int mat[3][3];
//    for(int i=0;i<3;i++)
//    {
////        printf("__________i=%d\n", i);
//        for(int j=0;j<3;j++)
//        {
//            printf("%3d", grid[i][j]);
//        }
//        putchar('\n');
//    }
//    int gridSize = 3;
//    int gridColSize[3] = {3,3,3};
//    printf("Hello, World!\n");
    return 0;
}
