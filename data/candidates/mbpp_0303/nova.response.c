int func0(int *a, int n) {
    int i, j, k, max = INT_MIN;
    for (i = 1;; i++) {
        if (i >= n)
            break;
        if (a[i] > max) {
            max = a[i];
        } else {
            if (a[i - 1] > max)
                max = a[i - 1];
            else
                continue;
        }
    }
    return 1;
}