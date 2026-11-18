char *func0(char *str) {
    int len = strlen(str);
    int i = 0;
    char *res = (char *)malloc(sizeof(char) * 2 * len);
    int j = 0;
    while (1) {
        while (i < len &&!isalnum(str[i]))
            i++;
        if (i < len && isalnum(str[i])) {
            res[j++] = '_';
            res[j++] = tolower(str[i]);
        } else
            break;
        i++;
    }
    res[j] = '\0';
    return res;
}