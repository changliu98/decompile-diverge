int firstMissingPositive(int* nums, int numsSize) {
    int i, j, k;
    bool flag;

    for (i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            flag = true;
            break;
        }
    }

    if (! flag)
        return 1;

    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= 0 || nums[i] > numsSize)
            nums[i] = 1;
    }

    for (i = 0; i < numsSize; ++i) {
        nums[(nums[i] - 1) % numsSize] += numsSize;
    }

    for (i = 0; i < numsSize; ++i) {
        if (nums[i] <= numsSize)
            return i + 1;
    }

    return numsSize + 1;
}