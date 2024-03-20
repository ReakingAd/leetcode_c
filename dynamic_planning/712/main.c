/**
 * 712. 两个字符串的最小ASCII删除和
 * 给定两个字符串s1 和 s2，返回 使两个字符串相等所需删除字符的 ASCII 值的最小和 。
    示例 1:

        输入: s1 = "sea", s2 = "eat"
        输出: 231
        解释: 在 "sea" 中删除 "s" 并将 "s" 的值(115)加入总和。
        在 "eat" 中删除 "t" 并将 116 加入总和。
        结束时，两个字符串相等，115 + 116 = 231 就是符合条件的最小和。

    示例 2:
        输入: s1 = "delete", s2 = "leet"
        输出: 403
        解释: 在 "delete" 中删除 "dee" 字符串变成 "let"，
        将 100[d]+101[e]+101[e] 加入总和。在 "leet" 中删除 "e" 将 101[e] 加入总和。
        结束时，两个字符串都等于 "let"，结果即为 100+101+101+101 = 403 。
        如果改为将两个字符串转换为 "lee" 或 "eet"，我们会得到 433 或 417 的结果，比答案更大。
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
/**
 *
 * dp[i][j] 代表s1(0,i)与s2(0,j)的最小ASCII删除和
 * 1) 如果 s1(i) == s2(j), 那么 dp[i][j] = dp[i-1][j-1]
 * 2) 如果 s1(i) != s2(j), 那么 dp[i][j] = min[ dp[i-1][j] + si(i), dp[i][j-1] + s2(j) ]
 *
 * 由于第一行，第一列的dp数值时，需要累加字符串多个字符串的值。例如s -- eat 需要累加e,a,t，就需要遍历。
 * 为了统一计算方式，可以多加入一行一列，用于"" -- eat 针对这种一个空字符串，一个多字符的字符串的过程，这样
 * 就逐个累加就行，省了遍历累加.
 *
 * 因此在取字符的ASCII值的时候，s1[i-1]才是第i个字符
 */
int minimumDeleteSum(char* s1, char* s2) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int dp[s1_len+1][s2_len+1]; // 为空字符串考虑，增加一行一列。
    for(int i=0;i<s1_len+1;i++)
    {
        for(int j=0;j<s2_len+1;j++)
        {
            // 第一行。即 “” - s2
            if(0 == i)
            {
                // 原点(0,0)处元素
                if(0 == j)
                {
                    dp[i][j] = 0;
                }
                // 除原点外，其他字符逐个累加就可以
                else
                {
                    dp[i][j] = dp[i][j-1] + s2[j-1];
                }
            }
            // >1 的行
            else
            {
                // 各行的首列，即 s1 -- ""
                if(0 == j)
                {
                    dp[i][j] = dp[i-1][j] + s1[i-1];
                }
                else
                {
                    dp[i][j] = s1[i-1] == s2[j-1]
                            ? dp[i-1][j-1]
                            : fmin(dp[i][j-1] + s2[j-1], dp[i-1][j] + s1[i-1]);
                }
            }
        }
    }
    return dp[s1_len][s2_len];
}
int main() {
//    "sea", s2 = "eat"
    char *s1 = "sea";
    char *s2 = "eat";
    int ans = minimumDeleteSum(s1, s2);
    printf("ans=%d\n", ans);
    return 0;
}
