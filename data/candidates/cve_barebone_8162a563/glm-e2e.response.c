int access_parse_oid(long *oid, size_t oid_len, char **out1, char **out2, long *out3, long *out4) {
    long count1;
    long count2;
    int i;

    // 1. Validate input arguments
    if (oid_len == 0 || oid == NULL) {
        return 1;
    }

    // 2. Extract counts from the OID array
    count1 = oid[0];
    count2 = oid[count1 + 1];

    // 3. Check if the total length matches the sum of components + 4 header elements
    if (oid_len != count1 + count2 + 4) {
        return 1;
    }

    // 4. Validate output pointers
    if (out1 == NULL || out2 == NULL) {
        return 1;
    }

    // 5. Allocate memory for the first string
    *out1 = malloc(count1 + 1);
    if (*out1 == NULL) {
        return 1;
    }

    // 6. Allocate memory for the second string
    *out2 = malloc(count2 + 1);
    if (*out2 == NULL) {
        free(*out1);
        return 1;
    }

    // 7. Store the counts into the output parameters
    if (out3 != NULL) {
        *out3 = count2;
    }
    if (out4 != NULL) {
        *out4 = count1;
    }

    // 8. Copy elements for the first string
    for (i = 0; i < count1; i++) {
        if (oid[i + 1] > 0xFF) {
            free(*out1);
            free(*out2);
            return 1;
        }
        (*out1)[i] = (char)oid[i + 1];
    }
    (*out1)[count1] = '\0';

    // 9. Copy elements for the second string
    for (i = 0; i < count2; i++) {
        if (oid[i + count1 + 2] > 0xFF) {
            free(*out1);
            free(*out2);
            return 1;
        }
        (*out2)[i] = (char)oid[i + count1 + 2];
    }
    (*out2)[count2] = '\0';

    // 10. Extract remaining trailing elements from the OID array
    if (out3 != NULL) {
        *out3 = oid[count1 + count2 + 2];
    }
    if (out4 != NULL) {
        *out4 = oid[count1 + count2 + 3];
    }

    return 0;
}