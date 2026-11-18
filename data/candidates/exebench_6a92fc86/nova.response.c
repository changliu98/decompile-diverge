int parse_width(char *s, int *num) {
    int i, tmp, len;

    i = tmp = 0;
    while (1) {
        if (s[i] == 0)
            break;
        if (s[i] < '0' || s[i] > '9')
            continue;
        len = s[i] - '0';
        tmp = tmp * 10 + len;
        i++;
    }
    *num = i;
    return tmp;
}