char *sdsmapchars(char *str, char *charset, char *replace, size_t replace_len) {
    size_t i, j, len = strlen(str);

    for (i = 0; i < len; i++) {
        for (j = 0; j < replace_len; j++) {
            if (str[i] == charset[j]) {
                str[i] = replace[j];
                break;
            }
        }
    }

    return str;
}