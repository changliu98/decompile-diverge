int sgl_len(int n) {
    n = n - 1;
    return (n * 3 >> 1) + (n & 1) + 2;
}