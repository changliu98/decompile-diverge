void testfunc16(int *a, int *b, int *c, int *d, int *e) {
    if (*a > 100) {
        goto l10;
    }
    if (*e > 100) {
        goto l10;
    }
    e++;
l10:
    e += 4;
    b++;
    if (*c > 1000) {
        goto l20;
    }
    if (*d < 100) {
        goto l20;
    }
    *c += *d;
l20:;
}