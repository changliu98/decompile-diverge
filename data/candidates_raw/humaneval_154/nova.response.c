bool func0(char *s, char *t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    char *str = (char *)malloc(sizeof(char) * (len_t * 2 + 1));
    bool flag = false;
    for (int i = 0; i < len_t; i++) {
        strncpy(str + i, t + i, len_t - i);
        strncpy(str + i + len_t, t, i);
        str[len_t * 2] = '\0';
        if (strstr(s, str)!= NULL) {
            free(str);
            flag = true;
            break;
        }
    }
    free(str);
    return flag;
}