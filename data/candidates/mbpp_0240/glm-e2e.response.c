void func0(int *a, int a_size, int *b, int b_size, int *out) {
    for (int i = 0; i < a_size - 1; i++) {
        out[i] = a[i];
    }
    for (int i = 0; i < b_size; i++) {
        out[a_size - 1 + i] = b[i];
    }
}