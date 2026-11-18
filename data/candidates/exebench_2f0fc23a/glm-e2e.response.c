void next(int *a, int *b, int c) {
    (*b)++;
    if (*b == c) {
        *b = 0;
        (*a)++;
    }
}