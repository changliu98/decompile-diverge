char* strtoupper(char* str) {
    int len = 8;
    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        str[i] = c;
    }
    return str;
}