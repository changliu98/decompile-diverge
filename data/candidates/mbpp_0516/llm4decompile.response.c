void func0(int *nums, int size)
{
    int i, j, k, max, key, placement = 1;
    int *temp = NULL, *count = NULL;

    max = nums[0];
    for (i = 1; i < size; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }

    temp = (int *)malloc(size * sizeof(int));
    count = (int *)malloc(10 * sizeof(int));

    while (placement <= max) {

        for (i = 0; i < 10; i++) {
            count[i] = 0;
        }

        for (j = 0; j < size; j++) {
            key = (nums[j] / placement) % 10;
            count[key]++;
        }

        for (k = 1; k < 10; k++) {
            count[k] += count[k - 1];
        }

        for (j = size - 1; j >= 0; j--) {
            key = (nums[j] / placement) % 10;
            temp[count[key] - 1] = nums[j];
            count[key]--;
        }

        for (j = 0; j < size; j++) {
            nums[j] = temp[j];
        }

        placement *= 10;
    }

    free(temp);
    free(count);
}