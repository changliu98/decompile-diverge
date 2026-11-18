int *func0(int *nums, int numsSize, int *returnSize) {
    int *res = (int *)malloc(sizeof(int) * numsSize);
    int i, j, k;
    int count = 0;
    for (i = 0; i < numsSize;) {
        int flag = 0;
        for (j = 0; j < count;) {
            if (nums[i] == res[j]) {
                flag = 1;
                break;
            }
            j++;
        }
        if (flag == 0) {
            res[count++] = nums[i];
        }
        i++;
    }
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count;) {
            if (res[i] > res[j]) {
                int tmp = res[i];
                res[i] = res[j];
                res[j] = tmp;
            }
            j++;
        }
    }
    *returnSize = count;
    return res;
}