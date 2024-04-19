/**
 * 1143. 最长公共子序列
 * 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
    一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
    例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
    两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
/**
 * 常规dp
 * 维护一个二维dp数组，先定义text1长度作为列数，text2长度作为行数。
 *
 * dp[i][j]含义：text1的0~j子串与text2的0~i子串的最长公共子序列的长度。
 *
 * 递推关系：
 *   1. text1子串结尾与text2子串结尾相同，则dp[i][j] = dp[i-1][j-1] + 1
 *   2. text1子串结尾与text2子串结尾不同，则dp[i][j] = max( dp[i-1][j], dp[i][j-1] )
 *
 * 最终二维数组dp中，最大的成员就是最终答案。
 * 显然dp数组是从左上逐步递推出右下，这就要求dp的第一行、第一列应该有初始状态。
 * 方式一：对于第一行，遍历逐个赋值为0，直到第一次遇到与text2[0]相等的字符，后面都赋值为1.第一列同理。
 *        此方法不会改变时间复杂度，但是会增加两个n次for循环的执行时间。用例超时。
 * 方式二：在原本的i行j列的dp数组基础上，多增加一行一列，并将dp所有元素都初始化为0。然后递推dp数组时
 *       的两层for循环都从下标1开始，这样就避免了对边界的特殊处理。统一使用递推关系来更新dp就可以了。
 */
int longestCommonSubsequence(char* text1, char* text2) {
    int ans = INT_MIN;
    int cols = strlen(text1);
    int rows = strlen(text2);
    int dp[rows+1][cols+1];
    memset(dp, 0, sizeof(dp));
    for(int i=1;i<rows+1;i++)
    {
        for(int j=1;j<cols+1;j++)
        {
            char c1 = text1[j-1];
            char c2 = text2[i-1];
            if(c1 == c2) {
                dp[i][j] = dp[i-1][j-1] + 1;
                ans = fmax(ans, dp[i][j]);
            }
            else
            {
                int max = fmax(dp[i][j-1], dp[i-1][j]);
                dp[i][j] = max;
                ans = fmax(ans, dp[i][j]);
            }
        }
    }
    for(int i=0;i<rows+1;i++)
    {
        for(int j=0;j<cols+1;j++)
        {
            printf("%4d",dp[i][j]);
        }
        putchar('\n');
    }
    return ans;
}
int main() {
//    text1 = "abcde", text2 = "ace"
    char *text1, *text2;
    text1 = "abcde";
    text2 = "ace";
    int ans = longestCommonSubsequence(text1, text2);
    printf("ans=%d", ans);
    return 0;
}
