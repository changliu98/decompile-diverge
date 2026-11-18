int func0(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int val = arr[i];
        if (val < 0) {
            val = -val;
        }
        while (val > 0) {
            sum += val % 10;
            val /= 10;
        }
    }
    return sum;
}