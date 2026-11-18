int func0(int *arr, int n) {
    int i, j, max, temp[n];
    for (i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && temp[i] < arr[i] * temp[j]) {
                temp[i] = arr[i] * temp[j];
            }
        }
    }
    max = temp[0];
    for (i = 1; i < n; i++) {
        if (temp[i] > max) {
            max = temp[i];
        }
    }
    return max;
}