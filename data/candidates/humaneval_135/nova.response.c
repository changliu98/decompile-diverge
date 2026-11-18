int func0(int *a, int n) {
    int i, func0 = -1;
    for (i = 1;; i++) {
        if (i >= n)
            break;
        if (a[i] < a[i - 1])
            func0 = i;
    }
    return func0;
}