static void bmp_iter_next(int *a, int *b) {
    *a = *a >> 1;
    *b = *b + 1;
}