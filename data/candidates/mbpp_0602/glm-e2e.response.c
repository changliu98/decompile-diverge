char func0(const char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        char c = str[i];
        int count = 0;
        for (int j = 0; j <= i; j++) {
            if (str[j] == c) {
                count++;
            }
        }
        if (count > 1) {
            return c;
        }
    }
    return '0';
}