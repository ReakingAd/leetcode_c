/**
 * 139. 单词拆分
 * 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
 * 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 *
 * 示例 1：
    输入: s = "leetcode", wordDict = ["leet", "code"]
    输出: true
    解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。

   示例 2：
    输入: s = "applepenapple", wordDict = ["apple", "pen"]
    输出: true
    解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
         注意，你可以重复使用字典中的单词。

    示例 3：
    输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    输出: false
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/**
 * 判断字符串s是否可以被字典表示
 */
bool inDict(char* s, char** wordDict, int wordDictSize)
{
    for(int i=0;i<wordDictSize;i++)
    {
        if(0 == strcmp(s, wordDict[i])) return true;
    }
    return false;
}
// 截取字符串s的[start,end]作为新字符串返回
char *substr(char *s, int start, int end)
{
    char *sub_s = (char *)malloc(sizeof(char) * (end-start + 2));
    int p=0;
    for(int i=start;i<=end;i++)
    {
        sub_s[p] = s[i];
        p++;
    }
    sub_s[p] = '\0';
    return sub_s;
}
unsigned long long hash(char *s, int left, int size)
{
    unsigned long long result = 0;
    for(int i=left;i<size;i++)
    {
        result = result * 2333ull;
        result += s[i] - 'a' + 1;
    }
    return result;
}
bool query(unsigned long long *hash_dict, int dict_len, unsigned long long target)
{
     for(int i=0;i<dict_len;i++)
     {
         if(hash_dict[i] == target) return true;
     }
    return false;
}
/**
 * dp[i] 存放的是s的子串[0,i]是否可以被字典表示
 * 递推关系： f(i) = 遍历j属于0~i： f(j) && [j+1]可以被字典表示
 */
bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    // 将字符串数组映射为一个hash值组成的数组。用于后续的搜索。
    unsigned long long hash_dict[wordDictSize];
    for(int i=0;i<wordDictSize;i++)
    {
        hash_dict[i] = hash(wordDict[i], 0, strlen(wordDict[i]));
    }
    int s_len = strlen(s);
    bool dp[s_len];
    memset(dp, false, s_len);
    char *sub_str;
    for(int i=0;i<strlen(s);i++)
    {
        sub_str = substr(s,0,i);
        if(query(hash_dict, wordDictSize, hash(sub_str, 0, strlen(sub_str))))
        {
            dp[i] = true;
            continue;
        }
        for(int j=0;j<=i;j++)
        {
            sub_str = substr(s,j+1,i);
            if(dp[j] && query(hash_dict, wordDictSize, hash(sub_str, 0, strlen(sub_str))))
            {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s_len-1];
}

int main() {
    char *s = "leetcode";
    char **wordDict = (char **)malloc(sizeof(char *) * 2);
    wordDict[0] = "leet";
    wordDict[1] = "code";
//    unsigned long long test = hash(wordDict[0], 0, 4);
//    printf("%llu", test);
    bool ans = wordBreak(s, wordDict, 2);
    printf("ans=%d", ans);
    return 0;
}
