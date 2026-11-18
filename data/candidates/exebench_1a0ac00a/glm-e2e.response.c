void agrega(int *a, int *b, int c, int *d) {
    if (*a == -1) {
        *a = c;
        *b = c;
    } else {
        d[*b] = c;
        *b = c;
    }
    d[*b] = -1;
}