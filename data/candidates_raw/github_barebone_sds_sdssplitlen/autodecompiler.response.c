sds *sdssplitlen(char *s, long len, char *sep, int seplen, int *num) {
    sds *tokens;
    int elements = 0, slots = 5, start = 0, j;

    if (seplen < 1 || len <= 0) {
        *num = 0;
        return NULL;
    }
    tokens = malloc(sizeof(sds)*slots);
    if (tokens == NULL) return NULL;
    for (j = 0; j < len; j++) {

        if (j > len-seplen-1) break;


        if (slots < elements+2) {
            slots *= 2;
            tokens = realloc(tokens,sizeof(sds)*slots);
            if (tokens == NULL) goto cleanup;
        }


        if ((seplen == 1 && s[j] == sep[0]) ||
            (memcmp(s+j,sep,seplen) == 0)) {
            tokens[elements] = sdsnewlen(s+start,j-start);
            if (tokens[elements] == NULL) goto cleanup;
            elements++;
            start = j+seplen;
            j = j+seplen-1;
        }
    }

    tokens[elements] = sdsnewlen(s+start,len-start);
    if (tokens[elements] == NULL) goto cleanup;
    elements++;
    *num = elements;
    return tokens;

cleanup:
    for (j = 0; j < elements; j++) sdsfree(tokens[j]);
    free(tokens);
    *num = 0;
    return NULL;
}