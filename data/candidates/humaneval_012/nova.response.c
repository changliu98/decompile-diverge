char *func0(char *str[], int n) {
    char *max = str[0];
    int maxlen = 0;
    for (int i = 0; i < n; i++) {
        int len = strlen(str[i]);
        if (len > maxlen) {
            max = str[i];
            maxlen = len;
        }
    }
    return max;
}