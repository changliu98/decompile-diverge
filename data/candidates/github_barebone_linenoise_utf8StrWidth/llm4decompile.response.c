size_t utf8StrWidth(const char *s, size_t len)
{
    size_t width = 0;
    size_t i = 0;
    int after_zwj = 0;
    while (i < len) {
        uint32_t cp = utf8DecodeChar(s + i, &skip);

        size_t ansi_len = ansiEscapeLen(s + i, len - i);
        if (ansi_len > 0) {
            i += ansi_len;
            continue;
        }

        if (!after_zwj) {
            width += utf8CharWidth(cp);
        } else {
            after_zwj = 0;
        }

        if (isZWJ(cp)) {
            after_zwj = 1;
        }

        i += skip;
    }
    return width;
}