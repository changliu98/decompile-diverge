void func0(int *arr, int n, int a) {
    if (n <= 4) {
        int i, j = n - 2, k = 1;
        for (i = 3; i < n; i++) {
            arr[i - 1] = (j * i / 2) + a * i;
        }
    } else {
        int i, j = 6 - n, k = 1;
        for (i = 3; i < n; i++) {
            arr[i - 1] = (j * i / 2) + a * i;
        }
    }
}