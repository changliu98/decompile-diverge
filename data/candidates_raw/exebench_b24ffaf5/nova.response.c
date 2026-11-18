int func0(long *r, FILE *f) {
    int c;
    *r = fgetc(f);
    if (*r == EOF) {
        c = EOF;
    } else {
        c = 0;
    }
    return c;
}