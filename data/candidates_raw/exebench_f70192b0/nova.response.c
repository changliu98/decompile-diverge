int func0(int n, char s[]) {
    int i, j, sign;
    char *p;

    p = s;

    if (n < 0) {
        sign = -1;
        n = -n;
    } else {
        sign = 1;
    }

    i = n;
    do {
        j = i % 10;
        *p++ = j + '0';
        i /= 10;
    } while (i!= 0);

    *p = '\0';

    int len = p - s;

    for (i = 0; i < len / 2; i++) {
        char tmp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = tmp;
    }

    return p - s;
}