/**
 * 239. 滑动窗口最大值
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 * 返回 滑动窗口中的最大值 。
 *
 * 示例 1：
    输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
    输出：[3,3,5,5,6,7]
 */
#include <stdio.h>
#include <stdlib.h>
void print_arr(int* nums, int numsSize)
{
    for(int i=0;i<numsSize;i++)
    {
        printf("%3d", nums[i]);
    }
    printf("\n");
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 *
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int *result = (int*) malloc(*returnSize * sizeof(int));
    int index = 0;
    // 维护一个单调递减队列
    int queue[numsSize+1];
    int head = 1;
    int tail = 0;
//    * 示例 1：
//    输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
//    输出：[3,3,5,5,6,7]
    for(int i=0;i<numsSize;i++)
    {
        // 1. 队非空 且 队尾元素 < 新元素，出队
        while(tail >= head && nums[queue[tail]] < nums[i]){
            tail--;
        }
        // 2. 队尾入队
        tail++;
        queue[tail] = i;
        // 3. 队列在首次满元素后，for循环没循环一次，就得出队一次。因此要在队列里存for的index才能满足
        if(queue[head] <= queue[tail] - k) head++;
        // 4. 队列在首次满元素后，都使用一次元素
        if(i>=k-1)
        {
//            printf("%3d", nums[queue[head]]);
            result[index] = nums[queue[head]];
            index++;
        }
    }
    return result;
}
int main() {
//    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int nums[] = {1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
//    int k = 3;
    int k = 1;
    int resultSize;
    int* result = maxSlidingWindow(nums, numsSize, k, &resultSize);

    for(int i=0;i<resultSize;i++)
    {
        printf("%3d", result[i]);
    }
    free(result);
    return 0;
}
