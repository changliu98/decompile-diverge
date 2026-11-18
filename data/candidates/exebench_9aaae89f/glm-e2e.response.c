void pick(int *a, int *b) {
    (*b)++;
    if (*b >= 0x300) {
        (*a)++;
        *b = 0;
    }
    if (*a >= 0xb4) {
        *a = 0;
    }
}