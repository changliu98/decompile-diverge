char *func0(char *a, char *b)
{
    int i;
    int len_a = strlen(a);
    int len_b = strlen(b);
    int min_len = len_a < len_b ? len_a : len_b;
    char *output = malloc((size_t)(min_len + 1));
    if (output == NULL) {
        return NULL;
    }
    for (i = 0; i < min_len; i++) {
        output[i] = a[i] == b[i] ? '0' : '1';
    }
    output[min_len] = '\0';
    return output;
}