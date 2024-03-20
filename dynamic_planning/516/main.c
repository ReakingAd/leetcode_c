/**
 * 516. 最长回文子序列
 * 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
 * 子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
    示例 1：
        输入：s = "bbbab"
        输出：4
    解释：一个可能的最长回文子序列为 "bbbb" 。

    示例 2：
        输入：s = "cbbd"
        输出：2
        解释：一个可能的最长回文子序列为 "bb" 。
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
/**
 * dp[i][j] 存放的是 (i,j) 子串的最长回文子序列的长度
 * 1) 如果s[i] == s[j], 那么dp[i][j] = dp[i+1][j-1] + 2
 * 2) 如果s[i] != s[j], 那么dp[i][j] = MAX[ dp(i,j-1), dp(i+1,j) ]
 */
int longestPalindromeSubseq(char* s) {
    int s_len = strlen(s);
    int dp[s_len][s_len];
    for(int j=0;j<s_len;j++)
    {
        for(int i=j;i>=0;i--)
        {
            // 一个字符的子串
            if(i == j)
            {
                dp[i][j] = 1;
            }
            // 2个字符的子串
            else if(i+1 ==j)
            {
                if(s[i] == s[j]) dp[i][j] = 2;
                else dp[i][j] = 1;
            }
            // >2个字符的子串
            else
            {
                if(s[i] == s[j]) dp[i][j] = dp[i+1][j-1] +2;
                else dp[i][j] = fmax(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    return dp[0][s_len-1];
}
int main() {
//    char *s = "bbbab";
    char *s = "cbbd";
    int ans = longestPalindromeSubseq(s);
    printf("ans=%d", ans);
    return 0;
}
