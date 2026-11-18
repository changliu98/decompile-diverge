void itox(unsigned short n, char s[]) {
    unsigned short i = 0, j;
    char t[MAX_SHORT];

    if (n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    while (n) {
        j = n % 16;
        if (j < 10)
            t[i++] = j + '0';
        else
            t[i++] = j - 10 + 'a';
        n /= 16;
    }

    for (j = i; i > 0; i--)
        s[i - 1] = t[j - i];
    s[j] = '\0';
}