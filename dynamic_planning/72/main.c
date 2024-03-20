/**
 * 72. 编辑距离
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数。
   你可以对一个单词进行如下三种操作：
    插入一个字符
    删除一个字符
    替换一个字符

    示例 1：
        输入：word1 = "horse", word2 = "ros"
        输出：3
        解释：
        horse -> rorse (将 'h' 替换为 'r')
        rorse -> rose (删除 'r')
        rose -> ros (删除 'e')

    示例 2：
        输入：word1 = "intention", word2 = "execution"
        输出：5
        解释：
        intention -> inention (删除 't')
        inention -> enention (将 'i' 替换为 'e')
        enention -> exention (将 'n' 替换为 'x')
        exention -> exection (将 'n' 替换为 'c')
        exection -> execution (插入 'u')
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
/**
 * dp[i][j]存放的是word1中(0,i)子串，转换成word2中(0,j)子串的操作数
 * 1) 如果s1(i) == s2(j) dp[i][j] = dp[i-1][j-1]
 * 2) 如果s1(i) != s2(j) dp[i][j] = min[ dp[i-1][j] dp[i][j-1] dp[i-1][j-1] ] + 1
 *  - dp[i-1][j]  对应对 s(0,i-1)转成s(0,j)的操作数, 再加1代表 s(0,i)尾删一次转成s(0,i-1)也就是s(0,j)
 *  - dp[i][j-1]  对应对 s(0,i)转成s(0,j-1)的操作数， 再加1代表 s(0,i)尾插一次转成s(0,j)
 *  - dp[i-1][j-1] 对应对 s(0,i-1)子串转成s(0,j-1)的操作数。再加1代表对s(0,i)尾替换转成s(0,j)
 *
 *  可见矩阵中，(i,j)的值是由其左、左上、上三个相邻元素的值递推而来，也就是说dp二维数组的值是行数从上到下，每一行中
 *  从左到右递推而来。也就是外层for循环行i，内层for虚幻列j
 */
int minDistance(char* word1, char* word2) {
    int r_len = strlen(word1);
    int c_len = strlen(word2);
    if(0 == r_len) return c_len;
    else if(0 == c_len) return r_len;
    int dp[r_len][c_len];
    for(int i=0;i<r_len;i++)
    {
        for(int j=0;j<c_len;j++)
        {
            // 第一行
            if(0 == i)
            {
                // 第一列，也就是(0,0)起点处
                if(0 == j)
                {
                    dp[i][j] = word1[i] == word2[j] ? 0 : 1;
                }
                else
                {
                    dp[i][j] = word1[i] == word2[j] ? dp[i][j-1] : dp[i][j-1] + 1;
                }
            }
            // >1 的行
            else
            {
                // 第一列
                if(0 == j)
                {
                    dp[i][j] = word1[i] == word2[j] ? i : dp[i-1][j] + 1;
                }
                else
                {
                    dp[i][j] = word1[i] == word2[j] ? dp[i-1][j-1] : fmin(fmin(dp[i][j-1],dp[i-1][j-1]), dp[i-1][j]) + 1;
                }
            }
        }
    }
    for(int i=0;i<r_len;i++)
    {
        for(int j=0;j<c_len;j++)
        {
            printf("%4d", dp[i][j]);
        }
        putchar('\n');
    }
    return dp[r_len-1][c_len-1];
}
int main() {
//    char *word1 = "horse";
//    char *word2 = "ros";
    char *word1 = "pneumonoultramicroscopicsilicovolcanoconiosis";
    char *word2 = "ultramicroscopically";
//    printf("%c", word1[0]);
//    printf("%d", strlen(word1));
    int distance = minDistance(word1, word2);
    printf("distance=%d", distance);
    return 0;
}
