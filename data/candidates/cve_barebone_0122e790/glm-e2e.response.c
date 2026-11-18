const char *parse_content_length(const char *p, const char *end, long *val) {
    // Skip leading whitespace
    while (p < end) {
        if (*p == ' ' || *p == '\t' || (*p == '\r' && *(p + 1) == '\n') || (*p == '\n' && (*(p + 1) == ' ' || *(p + 1) == '\t'))) {
            p++;
        } else {
            break;
        }
    }

    if (p == end) {
        return NULL;
    }

    long v = 0;
    int count = 0;

    // Parse digits
    while (p < end && *p >= '0' && *p <= '9') {
        v = v * 10 + (*p - '0');
        if (v < 0) {
            return NULL; // Overflow check
        }
        count++;
        p++;
    }

    if (p == end || count == 0) {
        return NULL;
    }

    // Skip trailing whitespace
    while (p < end) {
        if (*p == ' ' || *p == '\t' || (*p == '\n' && (*(p + 1) == ' ' || *(p + 1) == '\t'))) {
            p++;
        } else {
            break;
        }
    }

    if (p == end) {
        return NULL;
    }

    // Check for CRLF or LF
    if (*p == '\n') {
        p++;
    } else if (*p == '\r') {
        p++;
        if (*p == '\n') {
            p++;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }

    *val = v;
    return p;
}