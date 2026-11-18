int zhalfstr(char *s) {
    char c = '0', d = '0';
    int i = -1, j = 0, k = 0;
    while (c!= '\0') {
        char t = s[++i];
        char v = (t - '0') / 2 + '0';
        v += (c & 1) * 5;
        s[i] = v;
        if (v == '0' && j == 0)
            j++;
        else
            k = 1;
        c = t;
    }
    if (i!= j)
        s[i] = '\0';
    else {
        s[0] = '0';
        s[1] = '\0';
    }
    return d;
}