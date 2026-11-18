int access_parse_oid(void **oid, size_t *out_total_len, char **buf1, char **buf2, size_t *len1, size_t *len2) {
    int ret = 1;
    int len_a;
    int len_b;
    int i;

    // Check for null pointers and basic validity
    if (oid == NULL || out_total_len == NULL || *out_total_len == 0) {
        return 1;
    }

    len_a = (int)(long)oid[0];
    len_b = (int)(long)oid[1];

    // Validate total length
    if (*out_total_len != len_a + len_b + 4) {
        return 1;
    }

    // Check output pointers
    if (buf1 == NULL || buf2 == NULL) {
        return 1;
    }

    // Allocate buffers (+1 for null terminator)
    *buf1 = malloc(len_a + 1);
    if (*buf1 == NULL) {
        return 1;
    }

    *buf2 = malloc(len_b + 1);
    if (*buf2 == NULL) {
        free(*buf1);
        return 1;
    }

    // Set output lengths
    *len2 = len_b;
    *len1 = len_a;

    // Copy first buffer
    for (i = 0; i < len_a; i++) {
        if (oid[i + 1] > 0xff) {
            free(*buf1);
            free(*buf2);
            return 1;
        }
        (*buf1)[i] = (char)oid[i + 1];
    }
    (*buf1)[len_a] = '\0';

    // Copy second buffer
    for (i = 0; i < len_b; i++) {
        if (oid[i + len_a + 2] > 0xff) {
            free(*buf1);
            free(*buf2);
            return 1;
        }
        (*buf2)[i] = (char)oid[i + len_a + 2];
    }
    (*buf2)[len_b] = '\0';

    // Extract trailing metadata
    *out_total_len = (size_t)oid[len_a + len_b + 2];
    *out_total_len = (size_t)oid[len_a + len_b + 3]; // Overwrites previous (matches assembly)

    ret = 0;
    return ret;
}