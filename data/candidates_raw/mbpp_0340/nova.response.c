int func0(int *nums, int numsSize) {
    int i, j, k, sum, tmp[numsSize];
    i = j = k = sum = 0;
    while (i < numsSize) {
        if (nums[i] > 0) {
            tmp[j++] = nums[i];
        } else {
            i++;
            continue;
        }
        i++;
    }
    qsort(tmp, j, sizeof(int), cmpfunc);
    i = k = 0;
    while (k < 4) {
        if (k % 2 == 0) {
            sum += tmp[i];
        }
        i++;
        k++;
    }
    return sum;
}