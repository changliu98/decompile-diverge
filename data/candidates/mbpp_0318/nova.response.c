int func0(int n) {
    int i, j, k, l, max = 0;
    for (i = 1;; i++) {
        for (j = 1; j < n - i; j++) {
            k = n - i - j;
            if (i * j * k > max)
                max = i * j * k;
        }
    }
    return max;
}