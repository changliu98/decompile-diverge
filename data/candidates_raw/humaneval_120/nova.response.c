void func0(int *arr, int n, int k, int *brr) {
    int i = 0, j = 0;
    while (i < n - 1) {
        j = 0;
        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    for (int i = 0; i < k; i++) {
        brr[i] = arr[n - k + i];
    }
}