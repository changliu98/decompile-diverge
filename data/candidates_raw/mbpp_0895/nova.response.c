int func0(int *arr, int n) {
    int i, j, k, l, m, temp, max;
    if (n == 1) {
        max = arr[0];
    } else {
        int b[n];
        b[0] = arr[0];
        if (arr[0] > arr[1]) {
            max = arr[0];
        } else {
            max = arr[1];
        }
        b[1] = max;
        for (i = 2; i < n; i++) {
            if (b[i - 1] > b[i - 2]) {
                max = b[i - 1];
            } else {
                max = b[i - 2];
            }
            b[i] = max;
            if (b[i] > arr[i]) {
                max = b[i];
            } else {
                max = arr[i];
            }
            b[i] = max;
        }
        max = b[n - 1];
    }
    return max;
}