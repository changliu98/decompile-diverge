char *strtoupper(char *str) {
    int i, j, k;
    int len = 8;
    for (i = 0; i < len;) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            k = str[i] - 'a' + 'A';
        } else {
            k = str[i];
        }
        str[i] = k;
        i++;
    }
    return str;
}