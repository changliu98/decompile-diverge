int func0(char *s) {
    int i, len = strlen(s);
    for (i = 0; i < len - 2; i++) {
        if (s[i]!= s[i + 2]) {
            char c = '\0';
            continue;
        } else {
            break;
        }
    }
    if (s[0] == s[1]) {
        char c = '\0';
    } else {
        char c = '\1';
    }
    return c & 1;
}