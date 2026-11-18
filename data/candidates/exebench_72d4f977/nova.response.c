int endGB(char *s, int *p) {
    *p = 0;
    return strstr(s, "mar") || strstr(s, "may") == s;
}