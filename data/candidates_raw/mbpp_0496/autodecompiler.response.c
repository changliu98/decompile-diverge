void sort(int *arr, int len, int n, int *sorted) {
    qsort(arr, (size_t)len, sizeof(int), compare);
    int i = 0;
    while (1) {
        if (i >= n) break;
        sorted[i] = arr[i];
        i++;
    }
}