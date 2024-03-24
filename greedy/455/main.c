/**
 * 455. 分发饼干
 * 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 * 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。
 * 如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

    示例 1:
        输入: g = [1,2,3], s = [1,1]
        输出: 1
        解释:
        你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
        虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
        所以你应该输出1。
    示例 2:
        输入: g = [1,2], s = [1,2,3]
        输出: 2
        解释:
        你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
        你拥有的饼干数量和尺寸都足以让所有孩子满足。
        所以你应该输出2.
 */
#include <stdio.h>
#include <stdlib.h>
/**
 * 快速排序 + 贪心
 * 【注意】 题目中g,s没说是有序的，所以得先排序
 * g=[10,9,8,7]   s=[5,6,7,8]
 * g，s都是默认递增排列的？
 * s，g两个指针指向数组的起点，
 *    - 饼干如果能匹配到孩子。则计数加1，孩子指针后移。
 *    - 饼干如果不能匹配到孩子。则计数不变，孩子指针后移
 */
void print_arr(int *arr, int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%3d", arr[i]);
    }
    putchar('\n');
}
int partition(int *arr, int left, int right)
{
    int pivot = arr[left];
    while(left < right)
    {
        while(left < right && arr[right] >= pivot)
            right--;
        arr[left] = arr[right];
        while(left < right && arr[left] <= pivot )
            left++;
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    return left; // 放回单签pivot所在的下标
}
int quick_sort(int *arr, int left, int right)
{
    int pivot_pos = partition(arr, left, right);
    if(pivot_pos > left)
        quick_sort(arr, left, pivot_pos-1);
    if(pivot_pos < right)
        quick_sort(arr, pivot_pos+1, right);
}
int compare(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
int findContentChildren(int* g, int gSize, int* s, int sSize) {
    if(0 == sSize) return 0;
    print_arr(g, gSize);
//    qsort(g, gSize, sizeof(int), compare); // 通常标准库的qsort也是用快速排序实现的
//    qsort(s, sSize, sizeof(int), compare);
    quick_sort(g, 0, gSize-1);
    quick_sort(s, 0, sSize-1);
    print_arr(g, gSize);
    int ans = 0; // 累加分配的次数
    int p_g = 0; // 孩子指针
    int p_s = 0; // 饼干指针
    while(p_g < gSize && p_s < sSize)
    {
        if(s[p_s] >= g[p_g])
        {
            ans += 1;
            p_s++;
            p_g++;
        }
        else p_s++;
    }
    return ans;
}
int main() {
    int gSize = 4;
    int *g = (int *)malloc(sizeof(int) * gSize);
//    g[0] = 1; g[1] = 2; g[2] = 3;
    g[0] = 10; g[1] = 9; g[2] = 8; g[3] = 7;
    int sSize = 4;
    int *s = (int*)malloc(sizeof(int) * sSize);
    s[0] = 5; s[1] = 6; s[2] = 7; s[3] = 8;
    int ans = findContentChildren(g, gSize, s, sSize);
    printf("ans=%d", ans);
    free(g);
    free(s);
    return 0;
}
