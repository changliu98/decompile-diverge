static inline size_t count_string(uint8_t *raw, uint8_t *end, int *infoout) {
    size_t len = end-raw;
    size_t i = 1;
    int info = 0;
    bool e = false;
    while (1) {
        for8(i, len, {
            if (strtoksa[raw[i]]) goto tok;
            e = false;
        });
        break;
    tok:
        if (raw[i] == '"') {
            i++;
            if (!e) {
                break;
            }
            e = false;
            continue;
        }
        if (raw[i] == '\\') {
            info |= IESC;
            e = !e;
        }
        i++;
    }
    *infoout = info;
    return i;
}