int func0(int *nums, int numsSize) {
    int max = 0;
    int cur = 0;
    int i, j;

    for (i = 0; ; ++i) {
        if (i >= numsSize - 1)
            break;

        for (j = 0; ; ++j) {
            if (j >= numsSize - i - 1)
                break;

            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    int *arr = (int *)malloc(sizeof(int) * numsSize);
    int index = 0;
    arr[index++] = nums[0];

    for (i = 1; ; ++i) {
        if (i >= numsSize)
            break;

        if (nums[i] != nums[i - 1])
            arr[index++] = nums[i];
    }

    for (i = 0; ; ++i) {
        if (i >= index)
            break;

        if (i > 0 && arr[i] == arr[i - 1] + 1)
            cur++;
        else
            cur = 1;

        if (max < cur)
            max = cur;
    }

    free(arr);

    return max;
}