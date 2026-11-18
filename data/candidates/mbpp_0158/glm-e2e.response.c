int func0(int *arr, int n, int k) {
    int max = arr[0];
    int sum = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int j = 0; j < n; j++) {
        if ((max - arr[j]) % k != 0) {
            return -1;
        }
        sum += (max - arr[j]) / k;
    }

    return sum;
}