char **func0(char **strings, int size, char *substring, int *out_size)
{
    int i;
    int count = 0;
    char **out = NULL;
    for (i = 0; i < size; i++) {
        if (strstr(strings[i], substring) != NULL) {
            out = realloc(out, (size_t)(count + 1) * sizeof(char *));
            out[count] = strings[i];
            count++;
        }
    }
    *out_size = count;
    return out;
}