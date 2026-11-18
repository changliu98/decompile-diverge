static int64_t vcolon(const uint8_t *json, int64_t len, int64_t i) {
    if (i == len) return -(i+1);
    if (json[i] == ':') return i+1;
    do {
        switch (json[i]) {
        case ' ': case '\t': case '\n': case '\r': continue;
        case ':': return i+1;
        default: return -(i+1);
        }
    } while (++i < len);
    return -(i+1);
}