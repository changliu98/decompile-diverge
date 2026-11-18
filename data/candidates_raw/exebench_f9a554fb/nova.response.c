void func0(short *a, unsigned int n, short *b) {
    unsigned int i = 0;
    while (i < n) {
        b[i] += a[i];
        i++;
    }
}