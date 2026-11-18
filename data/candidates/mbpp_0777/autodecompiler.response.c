int func0(int* nums, int numsSize) {
    qsort(nums, (size_t)numsSize, sizeof(int), &compare);
    int i, result = nums[0];
    for (i = 0; ; i++) {
        if (i >= numsSize - 1) break;
        if (nums[i] != nums[i + 1]) {
            result += nums[i + 1];
        }
    }
    return result;
}