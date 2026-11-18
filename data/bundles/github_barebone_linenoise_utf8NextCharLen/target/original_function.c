static size_t utf8NextCharLen(const char *buf, size_t pos, size_t len) {
    if (pos >= len) return 0;

    size_t total = 0;
    size_t curpos = pos;

    /* Get the first codepoint. */
    size_t cplen;
    uint32_t cp = utf8DecodeChar(buf + curpos, &cplen);
    total += cplen;
    curpos += cplen;

    int isRI = isRegionalIndicator(cp);

    /* Consume any extending characters that follow. */
    while (curpos < len) {
        size_t nextlen;
        uint32_t nextcp = utf8DecodeChar(buf + curpos, &nextlen);

        if (isZWJ(nextcp) && curpos + nextlen < len) {
            /* ZWJ: include it and the following character. */
            total += nextlen;
            curpos += nextlen;
            /* Get the character after ZWJ. */
            nextcp = utf8DecodeChar(buf + curpos, &nextlen);
            total += nextlen;
            curpos += nextlen;
            continue;  /* Check for more extending after the joined char. */
        } else if (isGraphemeExtend(nextcp)) {
            /* Variation selector, skin tone, combining mark, etc. */
            total += nextlen;
            curpos += nextlen;
            continue;
        } else if (isRI && isRegionalIndicator(nextcp)) {
            /* Second regional indicator for a flag pair. */
            total += nextlen;
            curpos += nextlen;
            isRI = 0;  /* Only pair once. */
            continue;
        } else {
            break;
        }
    }

    return total;
}