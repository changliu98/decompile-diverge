float func0(float *arr, int n) {
    int i, j;
    float tmp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    if (n % 2 == 1) {
        tmp = arr[n / 2];
    } else {
        tmp = (arr[n / 2] + arr[n / 2 - 1]) / 2.0;
    }

    return tmp;
}