/**
 * 115. 不同的子序列
 * 给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数，结果需要对 109 + 7 取模。

    示例 1：
        输入：s = "rabbbit", t = "rabbit"
        输出：3
        解释：
        如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
        rabbbit
        rabbbit
        rabbbit

    示例 2：
        输入：s = "babgbag", t = "bag"
        输出：5
        解释：
        如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。
        babgbag
        babgbag
        babgbag
        babgbag
        babgbag

 */
#include <stdio.h>
#include <string.h>
/**
 * dp[i][j] 代表s(0,i) 中t(0,j)出现的个数
 * 1) 如果s[0,i] == t[0,j]
 *   - 不使用s[i]进行匹配。则 dp[i][j] = dp[i-1][j]
 *   - 使用s[i]进行匹配（也就是锁死s[i]与t[j]，直接忽略掉这俩字符） dp[i][j] = dp[i-1][j-1]
 *
 *   综合起来，则 dp[i][j] = dp[i-1][j] + dp[i-1][j-1]
*  2) 如果s[0,i] != t[0,j] 那么 dp[i][j] = dp[i-1][j]
 *
 *  再考虑遍历顺序。
 *  首先，i的长度 >= j的长度，才有意义。
 *  其次，根据递推公式， dp[i][j]依赖其左上、上 两个相邻元素。因此二维数组要从先上后下，先左后右的方向遍历。
 *
 *  对接线上的元素也是边界，也得单独考虑。因为对角线元素的上方是无意义的格子，不能作为递推的基数。
 *
 *  【细节】
 *  1. 内层for循环，是针对列的。因为行数>=列数。所以单单j<=i会越界，要增加限制条件j<t_len
 *  2. 测试用例字符串长度的取值范围在 1 <= s.length, t.length <= 1000。使用int dp[][]二维数组
 *     会溢出。改为unsigned long long dp[][]可通过测试用例
 *
 * 【x】 满足题目要求：在很多编程竞赛或算法问题中，题目会明确要求输出对某个数取模的结果。
 * 这是为了统一答案的格式，确保所有的解决方案都能在一个固定的范围内表示结果，方便比较和评判。
 */
int numDistinct(char* s, char* t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    if(s_len < t_len) return 0;
    unsigned long long dp[s_len][t_len];
    for(int i=0;i<s_len;i++)
    {
        for(int j=0;j<=i&&j<t_len;j++)
        {
            // 首行。因为有限制条件j<=i,所以这里也就是(0,0)原点处的元素
            if(0 == i)
            {
//                if(s[i] == t[j]) dp[i][j] = 1;
                dp[i][j] = s[i] == t[j] ? 1 : 0;
            }
            // 首列
            else if(0 == j)
            {
                dp[i][j] = s[i] == t[j] ? dp[i-1][j] + 1 : dp[i-1][j];
            }
            // 对角线上的元素
            else if(i == j)
            {
                dp[i][j] = s[i] == t[j] ? dp[i-1][j-1] : 0;
            }
            // 其他
            else
            {
                dp[i][j] = s[i] == t[j]
                        ? dp[i-1][j] + dp[i-1][j-1]
                        : dp[i-1][j];
            }
        }
    }
    return dp[s_len-1][t_len-1];
}
int main() {
//    输入：s = "rabbbit", t = "rabbit"
    char *s = "rabbbit";
    char *t = "rabbit";
    int ans = numDistinct(s, t);
    printf("result=%d\n", ans);
    return 0;
}
