/**
 * 5. 最长回文子串
 * 给你一个字符串 s，找到 s 中最长的回文子串。如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 *
 * 示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。

   示例 2：
    输入：s = "cbbd"
    输出："bb"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
void print_arr(bool dp[][5], int rowSize, int colSize)
{
    for(int i=0;i<rowSize;i++)
    {
        for(int j=0;j<colSize;j++)
        {
            printf("%d", dp[i][j]);
        }
        putchar('\n');
    }
}
char* longestPalindrome(char* s)
{
    int palindrome_len = INT_MIN; // 最长回文子串的长度
    int palindrome_start; // 最长回文子串的起点
    int palindrome_end; // 最长回文子串的终点
    int s_len = strlen(s);
    bool dp[s_len][s_len]; // 记录以i为起点，j为终点的子串是否是回文串
    // i行，j列。由于dp二维数组的起始状态时长度为1的子串，因此最先知道的是对角线上的值。
    // 递推关系 f(i,j)=f(i+1,j-1) && s[i]==s[j]可知元素值的递推依赖其左下方的元素。
    // 因此这里的循环得是外层循环列，内层循环行
    for(int j=0;j<s_len;j++)
    {
        for(int i=0;i<=j;i++)
        {
            // 长度为1的子串，也就是矩阵对角线位置上，
            if(i == j){
                dp[i][j] = true;
                if(j-i+1 > palindrome_len)
                {
                    palindrome_len = j-i+1;
                    palindrome_start = i;
                    palindrome_end = j;
                }
            }
            // 长度为2的子串，也就是紧挨着对角线的那条斜线
            else if(i+1 == j)
            {
                if(s[i] == s[j])
                {
                    dp[i][j] = true;
                    if(j-i+1 > palindrome_len)
                    {
                        palindrome_len = j-i+1;
                        palindrome_start = i;
                        palindrome_end = j;
                    }
                }
                else dp[i][j] = false;
            }
            else
            {
                if(dp[i+1][j-1] && s[i] == s[j])
                {
                    dp[i][j] = true;
                    if(j-i+1 > palindrome_len)
                    {
                        palindrome_len = j-i+1;
                        palindrome_start = i;
                        palindrome_end = j;
                    }
                }
                else dp[i][j] = false;
            }
        }
    }
    printf("len:%d,start=%d\n",palindrome_len,palindrome_start);
    char *ans = &s[palindrome_start];
    ans[palindrome_end] = '\0';
    return ans;
}
int main() {
//    char s[] = "babad";
    char s[] = "cbbd";
    char *ans = longestPalindrome(s);
    printf("%s, %d", ans, sizeof(s));
    return 0;
}
