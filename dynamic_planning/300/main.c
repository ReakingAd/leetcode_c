/**
 * 300. 最长递增子序列
 *
 * 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
 * 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列
    示例 1：
        输入：nums = [10,9,2,5,3,7,101,18]
        输出：4
        解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。

    示例 2：
        输入：nums = [0,1,0,3,2,3]
        输出：4
    示例 3：
        输入：nums = [7,7,7,7,7,7,7]
        输出：1
 */
#include <stdio.h>
#include <limits.h>
#include <math.h>
/**
 *  ----------------------------------------------------------------------------------
 *  ****第一版错误的思路****。 测试用例 [4,10,4,3,8,9] 通不过
 *  dp[i] 存放子数组[0,i]的最长严格递增子序列的长度
 *  1) 遍历找比nums[i]小，且dp值最大的那个，记为dp[k] = M, 那么dp[i] = dp[k] + 1;
 *  2) 如果遍历完，也没找到比nums[i]小的，那么dp[i] = dp[i-1]
 *  -----------------------------------------------------------------------------------
 *  【错误分析】: 上述思路中1)中，遍历得到的dp[k] = X,并不一定与nums[i]能继续组成严格递增子序列。所以 dp[i] = dp[k] + 1 也就不成立。
 *  因此，能保持这个 加1 的递推关系，dp[i]的定义就要修改一下：
 *
 *  dp[i]存放的是 以nums[i]为结尾且是原数组的严格递增子序列，最长的长度。
 *  递推关系：
 *    1) 遍历 nums[0] ~ nums[i-1], 在所有 < nums[i] 的值中找出最大的 dp[k] = M 则dp[i] = dp[k] + 1
 *    2) 如果 nums[0] ~ nums[i-1] 中所有值都 >=nums[i], 则dp[i] = 1;
 *  最后取dp[]数组的最大值就是题解。
 *
 */
int lengthOfLIS_1(int* nums, int numsSize) {
    int dp[numsSize];
    dp[0] = 1; // 第一个元素的最长严格递增子序列就是自身，长度是1
    for(int i=1;i<numsSize;i++)
    {
        int temp_index = -1; // nums数组下标缓存变量。用于寻找之前的最大dp
        int temp_dp = INT_MIN;// dp值缓存变量。用于寻找之前的最大dp
        for(int j=0;j<i;j++)
        {
            if(nums[j] < nums[i] && dp[j] > temp_dp) // nums[i] 能继续组成严格递增子序列
            {
                temp_index = j;
                temp_dp = dp[j];
            }
        }
        // 如果没找到比nums[i]小的。说明nums[i]不能参与构成最长严格递增子序列
        if(-1 == temp_index)
        {
            dp[i] = 1;
        }
        else
        {
            dp[i] = dp[temp_index] + 1;
        }
    }
    int ans = INT_MIN;
    for(int i=0;i<numsSize;i++)
    {
        ans = fmax(ans, dp[i]);
    }
    return ans;
}
int lengthOfLIS_2(int* nums, int numsSize) {
    int dp[numsSize];
    for(int i=0;i<numsSize;i++) dp[i] = 1;
    int ans = 1;
    for(int i=1;i<numsSize;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j] < nums[i])
            {
                dp[i] = fmax(dp[i], dp[j] + 1);
            }
        }
        ans = fmax(ans, dp[i]);
    }
    for(int i=0;i<numsSize;i++)
    {
        printf("%3d", nums[i]);
    }
    putchar('\n');
    return ans;
}
// 二分查找
int bi_search(int *nums, int numsSize, int target)
{
    int left = 0 ;
    int right = numsSize - 1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] > target)
        {
            if(mid > 0 && target > nums[mid -1]) return mid;
            right = mid -1;
        }
        else if(nums[mid] < target)
        {
            left = mid + 1;
        }
    }
    return mid;
}
/**
 * LIS = Longest Increasing Subsequence 最长递增子序列
 * 方法二： 贪心 + 二分查找。时间复杂度 o(nlogn)
 * 贪心：要使最长子序列最长，那么每个放入第i个位置的元素都要尽可能小。
 *
 * arr[i] 存放构成长度为 i+1 的最长子序列的末位元素所能放的最小元素。
 * nums[0]直接放入arr[0]遍历nums数组的1 ~ numsSize-1。
 *      1. nums[i] > 当前arr的末位元素，则追加到arr末位
 *      2. nums[i] < 当前arr的末位元素。则在arr[0] ~ arr[末位]中查找位置k，使满足arr[k-1] < nums[i] && arr[k] >= nums[i]
 *        将arr[k]替换为nums[i]
 * 最终arr的长度就是最长递增子序列的长度。
 *
 * ## 解析：
 * 1. 注意：arr数组最终存放的不是最长递增子序列本身。
 *    arr[i]位置上的元素就如上述定义中说的那样，仅仅是构成长度为i-1的最长递增子序列的末位元素所能放的最小值。
 * 2. 维护这样一个arr有什么用？
 *    设想输入数据为[1,2,3,4,1000, 5,6,7]。在nums中从前到后遍历数据组成LIS时，先组成了[1,2,3,4,1000]，
 *    当对5进行决策时，5被1000挡住了。5既不能放在1000后面，又不能插入到1000前面（因为顺序不能颠倒）。
 *    这样后续比1000小的数字，都被1000挡住了，就错过了组成更长的自增子序列的可能。因此，对于1000后面的元素，
 *    当遇到能放在1000的位置上并且能构成LIS的元素，就应该替换掉1000，站在1000原本的位置上。
 *
 *    对于更一般的情况[1,3,4,7,1000, 2,5,6].在arr中用过大的数据占据位置的情况肯定不止1000一个数字。举例，当
 *    遍历到数字2时，他不能追加到当前LIS的末位，那么就要用2去优化LIS前部分的元素，让构成当前长度的LIS的末位
 *    元素是目前能选到的最小数字。
 *
 *    如此每个for循环到的元素，都对LIS的组成做了贡献。即使没有从末位插入，也优化了各个长度的LIS。为后续的数字
 *    决策时，提供了最优的前提。
 * 3. 时间复杂度o(nlogn)
 *    当nums[i]不能插入到arr末位，让他去优化前部arr[0] ~ arr[末位-1]时，如果arr是个递增序列的话，使用二分查找
 *    去找它应该优化的位置。二分的logn时间复杂度，显然要快于for循环的n。
 *
 *    前面分析可知维护的arr并不是最终的LIS，那么arr是否是个递增子序列呢？看两种情况下对arr的操作：
 *    1. 追加到arr末位的操作，显然使arr保持递增
 *    2. 查找 arr[k-1] < nums[i] && arr[k] >= nums[i] 的位置，并替换位置k显然也不破坏arr的递增
 *    综上，arr是个递增序列，可以使用二分查找。
 *
 *
 * ## 对比【双层for循环dp】与【贪心+二分】
 * 【双层for循环dp】：当前状态下（遍历到nums[i]时），末位元素是定值，计算子序列长度最大值放入dp[i]
 * 【贪心+二分】：当前状态下（遍历到nums[i]时）, 最长递增子序列长度是定值，计算末位元素的最小值放入arr[i]
 *
 * 可见，一个算法是是固定A，找B的最值。另一个算法是固定B，找A的最值
 *
 */
int lengthOfLIS(int* nums, int numsSize) {
    int arr[numsSize];
    arr[0] = nums[0];
    int len = 1;
    for(int i=1;i<numsSize;i++)
    {
        if(nums[i] > arr[len-1])
        {
            arr[len] = nums[i];
            len++;
        }
        else
        {
            int pos = bi_search(arr, len, nums[i]);
            arr[pos] = nums[i];
        }
    }
    for(int i=0;i<numsSize;i++)
    {
        printf("%3d", arr[i]);
    }
    putchar('\n');
    return len;
}

int main() {
//    int nums[8] = {10,9,2,5,3,7,101,18};
//    int nums[3] = {3,1,2};
//    int nums[8] = {2, 3, 5, 7, 9,10,18, 101};
//    int nums[6] = {0,1,0,3,2,3};
        int nums[11] = {3,5,6,2,5,4,19,5,6,7,12};
//    int nums[9] = {1,3,6,7,9,4,10,5,6};
//    int pos = bi_search(nums, 8, 4);
//    printf("pos=%d", pos);

    int ans = lengthOfLIS(nums, 11);
    printf("ans=%3d\n", ans);
    return 0;
}
