/**
* 1137. 第n个泰波那契数
 * 泰波那契序列 Tn 定义如下：
 * T0 = 0, T1 = 1, T2 = 1, 且在 n >= 0 的条件下 Tn+3 = Tn + Tn+1 + Tn+2
 * 给你整数 n，请返回第 n 个泰波那契数 Tn 的值。
 * 示例 1：
    输入：n = 4
    输出：4
    解释：
    T_3 = 0 + 1 + 1 = 2
    T_4 = 1 + 1 + 2 = 4

    示例 2：
    输入：n = 25
    输出：1389537
*/
#include <stdio.h>
int tribonacci(int n){
    if(n<2) return n;
    if(2 == n) return 1;
    int a=0, b=0, c=1, d=1;
    for(int i=3;i<=n;i++)
    {
        a=b;
        b=c;
        c=d;
        d=a+b+c;
    }
    return d;
}
int main()
{
    // TODO: 二进制写入， 写入数字，读取数字
    int result = tribonacci(25);
//    printf("%d", result);
    char str[100];
    sprintf(str, "%d", result);
    FILE *fp = fopen("out.txt", "rb+");
    if(NULL == fp)
    {
        printf("can\'t open file.");
        return -1;
    }
    int num = 123456789;
    fwrite(&num, sizeof(int), 1, fp);
    rewind(fp);
    int result_read;
    fread(&result_read, sizeof(int), 1, fp);
    printf("read2=%d", result_read);
//    fprintf(fp, "str=%d", result);
//    rewind(fp);
//    char str2[100];
//    fgets(str2, 100, fp);
//    printf("%s",str2);
    fclose(fp);

//    char str[100];
//    sprintf(str, "pre_%d_post", result);
//    FILE *fp = fopen("out.txt", "r+");
//    fputs(str, fp);
//    rewind(fp);
//    char str2[100];
//    fgets(str2, 100, fp);
//    printf("str2=%s", str2);
//    fclose(fp);
    return 0;
}