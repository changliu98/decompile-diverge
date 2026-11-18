int func0(char *s) {
    int i, j;
    char flag;
    for (i = 0; i < strlen(s); i++) {
        for (j = i + 1; j < strlen(s); j++) {
            if (s[i] == s[j]) {
                flag = 0;
                break;
            } else
                flag = 1;
        }
    }
    return flag & 1;
}