int func0(int *arr, int n) {
    int i, j, k, l, m, temp, count = 0;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (k = 0; k < n; k++) {
        for (l = 1; l < n; l++) {
            if (arr[k] == arr[l]) {
                count++;
            }
        }
    }
    return count;
}