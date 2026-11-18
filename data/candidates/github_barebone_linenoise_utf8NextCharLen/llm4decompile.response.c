size_t utf8NextCharLen(const char *buf, size_t pos, size_t len)
{
    size_t cplen, nextlen, total;
    uint32_t cp, nextcp;
    int isRI;

    if (pos >= len)
        return 0;

    total = 0;
    cp = utf8DecodeChar(&buf[pos], &cplen);
    total += cplen;
    pos += cplen;

    isRI = isRegionalIndicator(cp);

    while (pos < len) {
        nextcp = utf8DecodeChar(&buf[pos], &nextlen);

        if (!isZWJ(nextcp) || pos + nextlen >= len) {
            if (isGraphemeExtend(nextcp)) {
                total += nextlen;
                pos += nextlen;
                continue;
            }

            if (isRI && isRegionalIndicator(nextcp)) {
                total += nextlen;
                pos += nextlen;
                isRI = 0;
                continue;
            }

            break;
        }

        total += nextlen;
        pos += nextlen;

        utf8DecodeChar(&buf[pos], &nextlen);
        total += nextlen;
        pos += nextlen;
    }

    return total;
}