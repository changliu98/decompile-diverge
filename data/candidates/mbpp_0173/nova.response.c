char *func0(char *s) {
    int i = 0, j = 0;
    char *result = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    while (1) {
        if (s[i]!= '\0') {
            if (isalpha(s[i])) {
                result[j++] = s[i];
            }
        } else {
            break;
        }
        i++;
    }
    result[j] = '\0';
    strcpy(s, result);
    return s;
}