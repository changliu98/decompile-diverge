static struct expr *func0(const char *cond, int *len) {
    int i = 0;
    const char *p = cond;
    while (*p) {
        if (!isspace(*p)) {
            break;
        }
        p++;
    }
    if (!*p) {
        return NULL;
    }
    do {
        char *end;
        int v = strtol(p, &end, 10);
        if (end!= p && (*end == ',' || *end == '\0')) {
            cond_values[i++] = v;
            break;
        }
        if (!isspace(*end)) {
            break;
        }
        p = end + 1;
    } while (1);
    do {
        const char *q = p;
        while (*q) {
            if (!isspace(*q)) {
                break;
            }
            q++;
        }
        if (!*q) {
            break;
        }
        p = q + 1;
    } while (1);
    *len = i;
    return (struct expr *)(uintptr_t)&cond_values;
}