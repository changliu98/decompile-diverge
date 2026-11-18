static int itostr(char *s, int i, int j) {
    int k, l;
    char c, *p;

    k = 0;
    if (i <= 0)
        l = k;
    else {
        if (j <= 0) {
            *s = '-';
            s++;
            i = -i;
            k++;
            j = -j;
        }
        while (i > 0) {
            *s = i % 10 + '0';
            s++;
            k++;
            i = -(i / 10);
            if (i <= 0)
                l = k;
        }
        if (i < 0) {
            *s = '\0';
            s--;
            while (s >= p) {
                c = *s;
                *s = *(s - 1);
                *(s - 1) = c;
                s--;
                p--;
            }
        }
    }
    return l;
}