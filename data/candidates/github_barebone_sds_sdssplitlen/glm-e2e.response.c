sds *sdssplitlen(const char *s, ssize_t length, const char *sep, int seplen, int *count) {
    int elements = 0;
    int slots = 5;
    size_t start = 0;
    sds *tokens;

    if (seplen < 1 || length <= 0) {
        *count = 0;
        return NULL;
    }

    tokens = malloc(sizeof(sds) * slots);
    if (!tokens) {
        return NULL;
    }

    for (size_t i = 0; i < length - (seplen - 1); i++) {
        // Check if we need to expand the tokens array
        if (slots < elements + 2) {
            slots *= 2;
            sds *newtokens = realloc(tokens, sizeof(sds) * slots);
            if (!newtokens) {
                goto cleanup;
            }
            tokens = newtokens;
        }

        // Match the separator
        if (seplen == 1) {
            if (s[i] == *sep) {
                goto match;
            }
        } else {
            if (memcmp(s + i, sep, seplen) == 0) {
                goto match;
            }
        }
        
        // Continue loop if no match
        continue;

    match:
        // Create a new SDS token from the substring
        tokens[elements] = sdsnewlen(s + start, i - start);
        if (!tokens[elements]) {
            goto cleanup;
        }
        elements++;
        start = i + seplen;
        i += seplen - 1;
    }

    // Add the remaining part of the string as the last token
    tokens[elements] = sdsnewlen(s + start, length - start);
    if (!tokens[elements]) {
        goto cleanup;
    }
    elements++;
    *count = elements;
    return tokens;

cleanup:
    // Free everything allocated so far on failure
    for (int j = 0; j < elements; j++) {
        sdsfree(tokens[j]);
    }
    free(tokens);
    *count = 0;
    return NULL;
}