int func0(char *s) {
    int i = 0, max = 0, j = 0;
    for (i = 0; i < strlen(s);) {
        if (s[i] == '[')
            i++;
        if (s[i] == ']')
            i--;
        if (i < 0)
            i = 0;
        if (i > max)
            max = i;
        if (i >= max - 1)
            break;
    }
    int res;
    if (i >= max - 1)
        res = 1;
    else
        res = 0;
    return res;
}