sds *__cdecl sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count) {
    sds *tokens;
    sds *newtokens;
    int slots = 5;
    int elements = 0;
    long start = 0;
    long j;

    // Return 0 if the separator is empty or the string length is not positive
    if (seplen < 1 || len <= 0) {
        *count = 0;
        return NULL;
    }

    tokens = (sds *)malloc(slots * sizeof(sds));
    if (!tokens) {
        return NULL;
    }

    for (j = 0; j < len - (seplen - 1); ++j) {
        // Check if we need to expand the tokens array
        if (slots < elements + 2) {
            slots *= 2;
            newtokens = (sds *)realloc(tokens, slots * sizeof(sds));
            if (!newtokens) {
                goto cleanup;
            }
            tokens = newtokens;
        }

        // Check if the separator matches at the current position
        if ((seplen == 1 && s[j] == *sep) || !memcmp(&s[j], sep, seplen)) {
            tokens[elements] = sdsnewlen(&s[start], j - start);
            if (!tokens[elements]) {
                goto cleanup;
            }
            ++elements;
            start = j + seplen;
            j = start - 1; // The loop's ++j will make it start at 'start' on the next iteration
        }
    }

    // Add the remaining part of the string as the last token
    tokens[elements] = sdsnewlen(&s[start], len - start);
    if (tokens[elements]) {
        *count = elements + 1;
        return tokens;
    }

cleanup:
    // If any allocation failed, clean up already created tokens and the array
    for (int i = 0; i < elements; ++i) {
        sdsfree(tokens[i]);
    }
    free(tokens);
    *count = 0;
    return NULL;
}