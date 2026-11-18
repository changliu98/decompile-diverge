bool func0(int *nums, int numsSize) {
    bool flag = false;
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == 0) {
                flag = true;
                break;
            }
        }
        if (flag)
            break;
    }
    return flag;
}