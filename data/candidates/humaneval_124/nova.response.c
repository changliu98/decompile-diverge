int func0(char *str) {
    if (strlen(str)!= 10)
        return 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (i < 10) {
            if (i == 2 || i == 5) {
                if (str[i]!= '-')
                    return 0;
            } else if (str[i] < '0' || str[i] > '9')
                return 0;
        }
    }
    char a[3], b[3], c[3], d[3];
    a[0] = str[0];
    a[1] = str[1];
    a[2] = '\0';
    b[0] = str[3];
    b[1] = str[4];
    b[2] = '\0';
    c[0] = str[6];
    c[1] = str[7];
    c[2] = '\0';
    d[0] = str[8];
    d[1] = str[9];
    d[2] = '\0';
    int a1 = atoi(a);
    int b1 = atoi(b);
    int c1 = atoi(c);
    if (a1 < 2 || a1 > 12)
        return 0;
    if (b1 < 1 || b1 > 31)
        return 0;
    if (a1 == 4 || a1 == 6 || a1 == 9 || a1 == 11) {
        if (b1 > 30)
            return 0;
    } else if (a1 == 2) {
        if (b1 > 29)
            return 0;
    }
    return 1;
}