/**
 * 63. 不同路径 II
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
 * 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
 * 网格中的障碍物和空位置分别用 1 和 0 来表示。
 * 示例 1：
 *  输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
    输出：2
    解释：3x3 网格的正中间有一个障碍物。
    从左上角到右下角一共有 2 条不同的路径：
    1. 向右 -> 向右 -> 向下 -> 向下
    2. 向下 -> 向下 -> 向右 -> 向右
 * 示例 2：
 *   输入：obstacleGrid = [[0,1],[0,0]]
 *   输出：1
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void print_matric(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
    for(int i=0;i<obstacleGridSize;i++)
    {
        for(int j=0;j<obstacleGridColSize[i];j++)
        {
            printf("%3d", obstacleGrid[i][j]);
        }
    }
}
/**
 * 使用二维dp数组
 */
//int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
//    int dp[obstacleGridSize][obstacleGridColSize[0]];
//    for(int i=0;i<obstacleGridSize;i++)
//    {
//        for(int j=0;j<obstacleGridColSize[i];j++)
//        {
//            if(1 == obstacleGrid[i][j]) dp[i][j] = 0;
//            else {
//                if(0 == i && 0 == j){
//                    dp[i][j] = 1;
//                }
//                else if(0==i){
//                    dp[i][j] = dp[i][j-1];
//                }
//                else if(0 == j){
//                    dp[i][j] = dp[i-1][j];
//                }
//                else {
//                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
//                }
//            }
//
//        }
//    }
//    return dp[obstacleGridSize-1][obstacleGridColSize[0]-1];
//}

/**
 * 滚动数组优化dp
 */
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize) {
    int curr; // 记录走到当前格子的走法种类。双层循环结束时，curr就是最终答案
    int prev; // 备份当前curr的计算结果。准备用于右侧下一个格子的递推
    int temp_arr[obstacleGridColSize[0]]; // 一维数组。同步备份记录当前格子的结果curr到数组的同一位置j。 准备用于下一行同一列格子的递推
    for(int i=0;i<obstacleGridSize;i++)
    {
        for(int j=0;j<obstacleGridColSize[i];j++)
        {
            // 当前格子有障碍物，直接走法即使0
            if(1 == obstacleGrid[i][j]){
                curr = 0;
            }
            // 当前格子无障碍物。使用递推关系f(i,j) = f(i-1,j) + f(i,j-1)
            else{
                if(0 == i)
                {
                    if(0 == j)
                    {
                        prev = 1; // 第一行第一列。初始化为1
                    }
                    curr = prev;
                }
                else
                {
                    if(0 == j)
                    {
                        prev = 0; // 非第一行，第一列。初始化为0
                    }
                    curr = temp_arr[j] + prev;
                }
            }
            temp_arr[j] = curr; // curr备份到数组
            prev = curr; // curr备份到prev
        }
    }
    return curr;
}
int main() {
    int obstacleGridSize = 3;
    int obstacleGridColSize[] = {3,3,3};
    int **obstacleGrid = (int **)malloc(sizeof(int *) * obstacleGridSize);
    for(int i=0;i<obstacleGridSize;i++)
    {
        obstacleGrid[i] = (int *)malloc(sizeof(int) * obstacleGridColSize[i]);
    }
    obstacleGrid[0][0] = 0; obstacleGrid[0][1] = 0; obstacleGrid[0][2] = 0;
    obstacleGrid[1][0] = 0; obstacleGrid[1][1] = 1; obstacleGrid[1][2] = 0;
    obstacleGrid[2][0] = 0; obstacleGrid[2][1] = 0; obstacleGrid[2][2] = 0;
    int result = uniquePathsWithObstacles(obstacleGrid, obstacleGridSize, obstacleGridColSize);
    printf("result=%d", result);
    return 0;
}
