/**
 * 704. 二分查找
 * 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
    示例 1:
        输入: nums = [-1,0,3,5,9,12], target = 9
        输出: 4
        解释: 9 出现在 nums 中并且下标为 4
    示例 2:
        输入: nums = [-1,0,3,5,9,12], target = 2
        输出: -1
        解释: 2 不存在 nums 中因此返回 -1
 */
#include <stdio.h>
#include <stdlib.h>
int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(target == nums[mid]) return mid;
        if(target < nums[mid])
        {
            right = mid - 1;
        }
        else if(target > nums[mid])
        {
            left = mid + 1;
        }
    }
    return -1;
}
int main() {
//    [-1,0,3,5,9,12]
    int numsSize = 6;
    int *nums = (int *)malloc(sizeof(int) * numsSize);
    nums[0] = -1; nums[1] = 0; nums[2] = 3;
    nums[3] = 5; nums[4] = 9; nums[5] = 12;
    int pos = search(nums, numsSize, 9);
    printf("pos=%d\n", pos);
    return 0;
}
