int func0(int *a, int n, int k) {
    int max = INT_MIN, i = 0, sum = 0;
    for (i = 0;; i++) {
        if (i < k * n) {
            sum = sum + a[i % n];
            if (max < sum)
                max = sum;
            if (sum < 0)
                sum = 0;
        } else
            break;
    }
    return max;
}