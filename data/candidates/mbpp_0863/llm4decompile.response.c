int func0(int *arr, int n) {
    int i, j, k;
    int count = 0;
    int ans = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    int *v = malloc((size_t) n * sizeof(int));
    int size_v = 1;
    v[0] = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) {
            v[size_v] = arr[i];
            size_v++;
        }
    }
    for (i = 0; i < size_v; i++) {
        if (i > 0 && v[i] == v[i - 1] + 1) {
            count++;
        } else {
            count = 1;
        }
        if (ans < count) {
            ans = count;
        }
    }
    free(v);
    return ans;
}