char *strtoupper(char *str) {
    int i;
    int len = 8;
    int j = 0;
    int k;
    while (j < len) {
        if (str[j] >= 97 && str[j] <= 122) {
            k = str[j] - 97 + 65;
        } else {
            k = str[j];
        }
        str[j] = k;
        j++;
    }
    return str;
}