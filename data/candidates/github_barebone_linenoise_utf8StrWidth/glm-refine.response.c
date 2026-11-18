size_t __cdecl utf8StrWidth(const char *s, size_t len)
{
    size_t width = 0;
    size_t i = 0;
    int after_zwj = 0;

    while (i < len)
    {
        uint32_t cp;
        size_t clen;

        cp = utf8DecodeChar(&s[i], &clen);

        // Check for ANSI escape sequences (ESC = 27)
        if (cp == 27)
        {
            size_t skip = ansiEscapeLen(&s[i], len - i);
            if (skip != 0)
            {
                i += skip;
                continue;
            }
        }

        // Handle Zero-Width Joiners (ZWJ)
        if (after_zwj)
        {
            // The character following a ZWI does not contribute to the width
            after_zwj = 0;
        }
        else
        {
            width += utf8CharWidth(cp);
        }

        if (isZWJ(cp))
        {
            after_zwj = 1;
        }

        i += clen;
    }

    return width;
}