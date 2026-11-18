int func0(int *nums, int numsSize) {
    int i, j, k, count = 0;
    for (i = 0;;) {
        for (j = i + 1;;) {
            if (j < numsSize) {
                if (nums[i]!= nums[j]) {
                    count++;
                } else {
                    break;
                }
            } else {
                break;
            }
            j++;
        }
        i = j;
        if (i >= numsSize) {
            break;
        }
    }
    return count;
}