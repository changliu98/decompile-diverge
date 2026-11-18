void func0(int n, int *out, int *size) {
    int capacity = 10;
    *size = 1;
    out[0] = 1;
    while (n != 1) {
        if (n % 2 == 1) {
            if (*size >= capacity) {
                capacity *= 2;
                out = realloc(out, (size_t)capacity * sizeof(int));
            }
            out[(*size)++] = n;
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
    }
    for (int i = 1; i < *size; ++i) {
        int tmp = out[i];
        int j;
        for (j = i - 1; j >= 0 && out[j] > tmp; --j) {
            out[j + 1] = out[j];
        }
        out[j + 1] = tmp;
    }
}