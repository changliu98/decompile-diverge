int func0(int *a, size_t n) {
    int max = a[0] * a[1];
    for (size_t i = 1; i < n - 1; i++) {
        int tmp = a[i] * a[i + 1];
        if (tmp > max)
            max = tmp;
    }
    return max;
}