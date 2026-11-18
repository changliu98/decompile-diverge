int* func0(const char *str, int *out_count) {
    int count = 0;
    const char *p = str;

    while (*p != '\0') {
        // Skip whitespace and hyphens
        while (*p != '\0' && !isspace(*p) && *p != '-') {
            p++;
        }
        
        if (*p == '\0') {
            break;
        }

        char *endp;
        int val = strtol(p, &endp, 10);

        if (p != endp && (*endp == ',' || *endp == '\0')) {
            func0_out[count] = val;
            count++;
        }

        // Skip until comma or end of string
        while (*endp != '\0' && *endp != ',') {
            endp++;
        }

        p = endp;
    }

    *out_count = count;
    return func0_out;
}