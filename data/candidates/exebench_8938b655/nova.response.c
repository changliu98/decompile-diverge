int itos(int n, char s[]) {
    int i, j, sign;
    char temp;

    if (n < 0) {
        sign = 0;
        n = -n;
        s[0] = '-';
    } else {
        sign = -1;
    }

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10)!= 0);

    s[i] = '\0';

    j = i + 1;

    if (sign < 0) {
        while (i-- >= 0) {
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
    }

    return j;
}