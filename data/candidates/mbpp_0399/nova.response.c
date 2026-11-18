void func0(int *a, int *b, int *out, int size) {
    int i;
    for (i = 0; i < size; i++) {
        out[i] = a[i] ^ b[i];
    }
}