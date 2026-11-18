char *func0(char *s) {
    int i = 0, j = 0;
    while (1) {
        if (s[j] == '\0') {
            break;
        }
        if (isalpha(s[j])) {
            if (!isupper(s[j])) {
                word[i++] = s[j];
            }
        }
        j++;
    }
    word[i] = '\0';
    return word;
}