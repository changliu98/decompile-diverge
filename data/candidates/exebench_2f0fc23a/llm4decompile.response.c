void next(int *i, int *j, int p) {
    *j += 1;
    if (*j == p) {
        *j = 0;
        *i += 1;
    }
}