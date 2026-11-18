int func0(const char *str, char c) {
    int pos = -1;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            pos = i;
        }
    }
    
    if (pos == -1) {
        return -1;
    } else {
        return pos + 1;
    }
}