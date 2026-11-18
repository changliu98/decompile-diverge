void sdsrange(char *s, long start, long end) {
    size_t len = sdslen(s);
    if (len == 0) {
        return;
    }

    // Adjust negative start index
    if (start < 0) {
        start += len;
        if (start < 0) {
            start = 0;
        }
    }

    // Adjust negative end index
    if (end < 0) {
        end += len;
        if (end < 0) {
            end = 0;
        }
    }

    // Calculate new length
    size_t newlen;
    if (start > end) {
        newlen = 0;
    } else {
        newlen = end - start + 1;
    }

    // Clamp start and end to string bounds
    if (newlen != 0) {
        if (start >= len) {
            newlen = 0;
        } else if (end >= len) {
            end = len - 1;
            newlen = end - start + 1;
        }
    }

    // Shift characters to the beginning if necessary
    if (start != 0 && newlen != 0) {
        memmove(s, s + start, newlen);
    }

    // Null-terminate and update the length
    s[newlen] = '\0';
    sdssetlen(s, newlen);
}