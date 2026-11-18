char **sdssplitlen(char *s, long len, char *sep, int seplen, int *count)
{
    char **tokens = ((void *)0);
    char **newtokens = ((void *)0);
    int elements = 0;
    int slots = 5;
    long i = 0;
    long start = 0;
    if (seplen < 1 || len < 1) {
        *count = 0;
        return ((void *)0);
    }
    tokens = (char **)malloc(sizeof(char *) * (slots));
    if (tokens == ((void *)0))
        return ((void *)0);
    for (i = 0; i < len - (seplen - 1); i++) {
        if (elements + 2 > slots) {
            slots = slots * 2;
            newtokens = (char **)realloc(tokens, sizeof(char *) * (slots));
            if (newtokens == ((void *)0))
                goto cleanup;
            tokens = newtokens;
        }
        if (seplen == 1 && s[i] == sep[0])
            goto found;
        if (memcmp(&s[i], sep, seplen) == 0)
        found:
            if (seplen == 1 && s[i] == sep[0])
                goto found;
            if (memcmp(&s[i], sep, seplen) == 0) {
                tokens[elements] = sdsnewlen(&s[start], i - start);
                if (tokens[elements] == ((void *)0))
                    goto cleanup;
                elements++;
                start = i + seplen;
                i = start - 1;
            }
    }
    tokens[elements] = sdsnewlen(&s[start], len - start);
    if (tokens[elements] == ((void *)0))
        goto cleanup;
    elements++;
    *count = elements;
    return tokens;
cleanup:
    for (int i = 0; i < elements; i++)
        sdsfree(tokens[i]);
    free(tokens);
    *count = 0;
    return ((void *)0);
}