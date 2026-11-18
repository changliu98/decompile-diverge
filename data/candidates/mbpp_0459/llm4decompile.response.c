char *func0(char *str1) {
    size_t i, j, len;
    char *str2;

    len = strlen(str1);
    str2 = malloc(len + 1);
    if (!str2) {
        return NULL;
    }

    for (i = 0, j = 0; i < len; i++) {
        if (!(1 << 8 & __ctype_b_loc()->mask[(int)(unsigned char)str1[i]])) {
            str2[j++] = str1[i];
        }
    }
    str2[j] = '\0';

    return str2;
}