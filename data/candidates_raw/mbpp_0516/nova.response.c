void func0(int *arr, int size) {
    int max = arr[0];
    int i, j;
    int *bucket;
    int step = 1;
    int *tmp;
    int k;
    int index;
    int count = 1;

    while (1) {
        bucket = (int *)malloc(sizeof(int) * size);
        for (i = 0; i < size; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        for (i = 0; i < size; i++) {
            index = arr[i] / step;
            bucket[index]++;
        }
        for (i = 1; i < 10; i++) {
            bucket[i] = bucket[i - 1] + bucket[i];
        }
        tmp = (int *)malloc(sizeof(int) * size);
        for (i = size - 1; i >= 0; i--) {
            index = arr[i] / step;
            tmp[--bucket[index]] = arr[i];
            bucket[index]--;
        }
        for (i = 0; i < size; i++) {
            arr[i] = tmp[i];
        }
        step *= 10;
        count++;
    }
    free(bucket);
    free(tmp);
}