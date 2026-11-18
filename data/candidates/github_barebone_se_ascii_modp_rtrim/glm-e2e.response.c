size_t modp_rtrim(char* str, size_t len) {
    while (len != 0) {
        char c = str[len - 1];
        if (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
            str[len - 1] = '\0';
            len--;
        } else {
            break;
        }
    }
    return len;
}