/**
 * 354. 俄罗斯套娃信封问题
 * 给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
 * 当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
 * 请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。

    注意：不允许旋转信封。
    示例 1：
        输入：envelopes = [[5,4],[6,4],[6,7],[2,3]]
        输出：3
        解释：最多信封的个数为 3, 组合为: [2,3] => [5,4] => [6,7]。
    示例 2：
        输入：envelopes = [[1,1],[1,1],[1,1]]
        输出：1
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * 方法一、 dp。 用例超时。时间复杂度是O(n^2)
 * 1) 先给数组排序，宽度w小的在前。宽度一致的话，高度小的在前。
 * 2) dp[i]的含义是，以第i个信封为最外层信封，共可以套几个信封
 *    递推关系： 遍历env[0] ~ env[i-1]，找到 能放进信封i，并且dp值最大的那个dp[k] = M, 则dp[i] = M+1
 *
 * dp中最大值就是题解
 */
int compare(const void *a, const void *b)
{
    int *pa = *(int**)a;
    int *pb = *(int**)b;
    if(pa[0] != pb[0]) return pa[0] - pb[0]; // 宽度w升序
//    return pa[1] - pb[1]; // 高度h升序
    return pb[1] - pa[1]; // 高度h降序
}
int maxEnvelopes_1(int** envelopes, int envelopesSize, int* envelopesColSize) {
    qsort(envelopes, envelopesSize, sizeof(envelopes[0]), compare);
    int ans = 1;
    int dp[envelopesSize];
    for(int i=0;i<envelopesSize;i++) dp[i] = 1;
    for(int i=1;i<envelopesSize;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
            {
                dp[i] = fmax(dp[i], dp[j] + 1);
                ans = fmax(ans, dp[i]);
            }
        }
    }
    for(int i=0;i<envelopesSize;i++)
    {
        printf("%3d", dp[i]);
    }
    putchar('\n');
    return ans;
}
/**
 * 方法二、二维问题优化为一维问题。
 * 将信封排序：宽度由低到高，高度由高到低。只需要比较高度就可以了。因为
 * - 对于宽度小于 dp[i]的信封，自然高度也小于dp[i]的高度就可以套娃。dp[i]=dp[j]+1
 * - 对于宽度等于 dp[i]的信封，由于高度是由高到低排序，if判断永远为false，在计算dp[i]时就不会同样宽度信封的基础上进行+1的操作。
 *   换句话说，所有宽度相同的信封，都只会在比他们宽度小的信封的基础上，计算dp值。
 *
 * 这个方法只是将问题从二维降为一维，排序后不用管宽度了，只需要考虑高度即可。但是时间复杂度没有变化依然是o(n^2)
 */
int maxEnvelopes_2(int** envelopes, int envelopesSize, int* envelopesColSize) {
    qsort(envelopes, envelopesSize, sizeof(envelopes[0]), compare);
    for(int i=0;i<envelopesSize;i++)
    {
        for(int j=0;j<envelopesColSize[i];j++)
        {
            printf("%3d", envelopes[i][j]);
        }
        putchar(',');
    }
    putchar('\n');
    int dp[envelopesSize];
    for(int i=0;i<envelopesSize;i++)
    {
        dp[i] = 1;
    }
    int ans = 1;
    for(int i=0;i<envelopesSize;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(envelopes[i][1] > envelopes[j][1])
            {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        ans = fmax(ans, dp[i]);
    }
    for(int i=0;i<envelopesSize;i++)
    {
        printf("%3d", dp[i]);
    }
    putchar('\n');
    return ans;
}

int lower_bound(int* arr, int arrSize, int val) {
    int left = 0, right = arrSize - 1;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (val < arr[mid]) {
            right = mid - 1;
        } else if (val > arr[mid]) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    if (arr[left] >= val) {
        return left;
    }
    return -1;
}
/**
 * 方法三：dp + 二分查找。时间复杂度o(nlogn), 这不好想到啊，不直观。
 * 先给数组排序，宽度从小到大。如果宽度一样，高度从大到小。后面比较时，只比较信封的高度
 * 遍历信封，当前信封是i
 * dp[j]存放的是，前i个信封组成的长度为j的套娃前提下，末位（也就是位置j）能放的信封的最小值。
 * 递推关系：
 *  1) 如果 信封i > 末位信封， dp[j] = dp[i]
 *  2) 如果 信封i < 末位信封，则在0 ~ j-1中寻找能位置k，k满足 dp[k]<信封i<dp[k+1]
 *          然后修改 dp[k+1] = 信封i。
 *     解释a：注意定义的dp的含义。最终构建完的dp，并不是套娃顺序。别想错了。
 *     解释b：信封数组是经过排序的，宽度由低到高。因此当前信封i在决定放入dp中的哪个位置前，都能确保信封i的宽度 >= dp中的任何一个
 *           值所代表的那个信封的宽度。也就是说，不管信封i被插入到dp中的哪个位置，都能保证前面的信封的宽度都小于信封i。这样在比较
 *           的时候，可以放心的只比较高度就行了。
 *     解释c：查找k时，使用二分查找，这就是时间复杂度o(nlogn)中logn的由来
 *
 * 末位信封的下标+1就是最终答案
 */
int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    qsort(envelopes, envelopesSize, sizeof(envelopes[0]), compare);
    for(int i=0;i<envelopesSize;i++)
    {
        for(int j=0;j<envelopesColSize[i];j++)
        {
            printf("%3d", envelopes[i][j]);
        }
        putchar(',');
    }
    int point = 0;
    int f[envelopesSize];
    f[point] = envelopes[0][1];
    point++;
    for(int i=0;i<envelopesSize;i++)
    {
        int height = envelopes[i][1];
        // 如果当前信封（的高度） > 末尾，插入到f末尾
        if(height > f[point-1])
        {
            f[point] = height;
            point++;
        }
        // 如果当前信封（的高度） < 末尾，查找位置k，使k满足 f[k] < 当前信封 < f[k+1]。修改f[k+1]为当前信封的值
        else
        {
            f[lower_bound(f, point, height)] = height;
        }
    }
    return point;
}
int main() {
    int envelopesSize = 9;
//    int envelopesColSize[4] = {2,2,2,2};
//    int envelopesColSize[8] = {2,2,2,2,2,2,2,2};
    int envelopesColSize[9] = {2,2,2,2,2,2,2,2,2};
    int **envelopes = (int**)malloc(sizeof(int*) * envelopesSize);
    for(int i=0;i<envelopesSize;i++)
    {
        envelopes[i] = (int *)malloc(sizeof(int) * envelopesColSize[i]);
    }
//    envelopes[0][0] = 5; envelopes[0][1] = 4;
//    envelopes[1][0] = 6; envelopes[1][1] = 4;
//    envelopes[2][0] = 6; envelopes[2][1] = 7;
//    envelopes[3][0] = 2; envelopes[3][1] = 3;
//    [[1,2],[2,3],[3,4],[4,5],[5,6],[5,5],[6,7],[7,8]]
//    [[1,2],[2,3],[3,4],[3,5],[4,5],[5,5],[5,6],[6,7],[7,8]]
    envelopes[0][0] = 1; envelopes[0][1] = 2;
    envelopes[1][0] = 2; envelopes[1][1] = 3;
    envelopes[2][0] = 3; envelopes[2][1] = 4;
    envelopes[3][0] = 3; envelopes[3][1] = 5;
    envelopes[4][0] = 4; envelopes[4][1] = 5;
    envelopes[5][0] = 5; envelopes[5][1] = 5;
    envelopes[6][0] = 5; envelopes[6][1] = 6;
    envelopes[7][0] = 6; envelopes[7][1] = 7;
    envelopes[8][0] = 7; envelopes[8][1] = 8;
    int ans = maxEnvelopes(envelopes, envelopesSize, envelopesColSize);
    printf("ans=%d", ans);
    free(envelopes);
    return 0;
}
