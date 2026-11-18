static size_t utf8StrWidth(const char *s, size_t len) {
    size_t width = 0;
    size_t i = 0;
    int after_zwj = 0;  /* Track if previous char was ZWJ */

    while (i < len) {
        size_t clen;
        uint32_t cp = utf8DecodeChar(s + i, &clen);

        /* Skip ANSI CSI escape sequences entirely: they produce no
         * glyph, so they must not contribute to the display width.
         * Checked before the ZWJ state so a stray ZWJ immediately
         * followed by ESC cannot swallow the ESC byte. */
        if (cp == 0x1b) {
            size_t skip = ansiEscapeLen(s + i, len - i);
            if (skip > 0) {
                i += skip;
                continue;
            }
        }

        if (after_zwj) {
            /* Character after ZWJ: don't add width, it's joined.
             * But do check for extending chars after it. */
            after_zwj = 0;
        } else {
            width += utf8CharWidth(cp);
        }

        /* Check if this is a ZWJ - next char will be joined. */
        if (isZWJ(cp)) {
            after_zwj = 1;
        }

        i += clen;
    }
    return width;
}