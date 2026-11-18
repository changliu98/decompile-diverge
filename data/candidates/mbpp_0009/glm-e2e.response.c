int func0(const char *s) {
    int len = strlen(s);
    char buf[2 * len + 1];
    strcpy(buf, s);
    strcat(buf, s);
    
    for (int i = 1; i <= len; i++) {
        int match = 1;
        for (int j = 0; j < len; j++) {
            if (s[j] != buf[i + j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return len;
}