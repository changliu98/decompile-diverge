int func0(char *a, char *b)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    char *tmp = malloc((size_t)(len_b * 2 + 1));
    for (int i = 0; i < len_b; i++) {
        strncpy(tmp, b + i, (size_t)(len_b - i));
        strncpy(tmp + len_b - i, b, (size_t)i);
        tmp[len_b] = '\0';
        if (strstr(a, tmp) != NULL) {
            free(tmp);
            return 1;
        }
    }
    free(tmp);
    return 0;
}