char *func0(char *str, char c) {
    int len = strlen(str);
    int i, j, k, l, m, n;
    char *str2;
    int first = -1, last = -1;
    for (i = 0; i < len; i++) {
        if (str[i] == c) {
            if (first == -1)
                first = i;
            last = i;
        }
    }
    while (1) {
        if (first!= -1 && last!= -1) {
            str2 = (char *)malloc(sizeof(char) * (len - 2 + 1));
            for (i = 0, j = 0; i < len; i++) {
                str2[j++] = str[i];
            }
            for (k = first + 1; k < last + 1; k++) {
                str2[j++] = str[k];
            }
            str2[j] = '\0';
            str = str2;
        } else {
            break;
        }
    }
    return str;
}