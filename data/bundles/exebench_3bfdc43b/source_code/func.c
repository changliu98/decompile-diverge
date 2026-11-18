
void norm(int *hi, int *lo, int base) {
    int n;
    if (*lo < 0) {
        n = (-*lo - 1)/base + 1;
        *hi -= n;
        *lo += n * base;
    }
    if (*lo >= base) {
        n = *lo / base;
        *hi += n;
        *lo -= n * base;
    }
}
