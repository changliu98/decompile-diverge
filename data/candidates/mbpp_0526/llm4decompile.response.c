char *func0(char *str1) {
    size_t len = strlen(str1);
    char *str2 = malloc(len + 1);
    if (!str2) {
        return NULL;
    }
    if (len > 0) {
        str2[0] = toupper(str1[0]);
        for (size_t i = 1; i < len; i++) {
            str2[i] = tolower(str1[i]);
        }
        str2[len - 1] = toupper(str2[len - 1]);
        str2[len] = '\0';
    }
    return str2;
}