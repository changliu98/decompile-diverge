bool endStrider(const char *str, int *result) {
    *result = 0;
    return strstr(str, "end") != NULL;
}