static void func0(char *p, int base, unsigned long long v) {
    char *start = p;
    unsigned long long q = v;
    int d, m;
    if (base == 'x') {
        m = 4;
    } else {
        m = 3;
    }
    if (v == 0) {
        *p++ = '0';
    }
    while (q > 0) {
        d = q % m;
        q /= m;
        *p++ = d + (d < 10? '0' : (base == 'x'? 'a' : 'A') - 10);
    }
    *p = '\0';
    reverse(start, p - 1);
}