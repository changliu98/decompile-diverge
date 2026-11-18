int bin2bitstr(unsigned int n, int *bits) {
    int i, j, k;
    unsigned int m;

    m = 1;
    j = 0;
    k = 0;
    while (1) {
        if (m <= n) {
            m *= 2;
            j++;
        } else {
            m /= 2;
            j--;
            break;
        }
    }

    for (i = j; i >= 0; i--) {
        if ((n - m) >= 0) {
            n -= m;
            bits[j - i] = 1;
        } else {
            bits[j - i] = 0;
        }
        m /= 2;
    }
    return j;
}