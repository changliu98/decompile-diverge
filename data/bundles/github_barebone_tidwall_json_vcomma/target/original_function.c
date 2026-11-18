static int64_t vcomma(const uint8_t *json, int64_t len, int64_t i, uint8_t end)
{
    if (i == len) return -(i+1);
    if (json[i] == ',') return i;
    do {
        switch (json[i]) {
        case ' ': case '\t': case '\n': case '\r': continue;
        case ',': return i;
        default: return json[i] == end ? i : -(i+1);
        }
    } while (++i < len);
    return -(i+1);
}