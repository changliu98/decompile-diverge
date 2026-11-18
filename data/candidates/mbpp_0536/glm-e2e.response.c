void func0(int *arr1, int n, int step, int *arr2, int *out_count) {
    int count = 0;
    for (int i = 0; i < n; i += step) {
        arr2[count] = arr1[i];
        count++;
    }
    *out_count = count;
}