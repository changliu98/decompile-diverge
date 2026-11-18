BITCODE_TU __cdecl bit_utf8_to_TU(char *str, const unsigned int cquoted)
{
    char *p;
    unsigned __int8 c;
    size_t len, i;
    BITCODE_RS *wstr;

    p = str;
    i = 0LL;
    len = strlen(str);

    // Limit maximum length
    if (len > 0xFFFE)
    {
        loglevel = 1;
        len = 65534LL;
    }

    wstr = (BITCODE_RS *)calloc(2uLL, len + 1);
    if (!wstr)
    {
        loglevel = 1;
        return 0LL;
    }

    while (len)
    {
        c = *p++;
        if (!c)
            break;

        --len;

        if (c >= 0x80)
        {
            // 2-byte UTF-8 sequence
            if ((c & 0xE0) == 0xC0)
            {
                if (len)
                {
                    wstr[i++] = ((c & 0x1F) << 6) | (p[1] & 0x3F);
                }
                --len;
                ++p;
            }
            // 3-byte UTF-8 sequence
            else if ((c & 0xF0) == 0xE0)
            {
                if (len >= 2)
                {
                    wstr[i++] = ((c & 0x0F) << 12) | ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
                }
                p += 2;
                len -= 2LL;
            }
        }
        // Handle escape sequences if cquoted is enabled
        else if (cquoted && c == '\\' && len > 1 && (*p == '"' || *p == '\\' || *p == 'r' || *p == 'n'))
        {
            c = *p++;
            if (c == 'r')
            {
                wstr[i++] = '\r'; // 13
            }
            else
            {
                if (c == 'n')
                    wstr[i++] = '\n'; // 10
                else
                    wstr[i++] = c;
            }
        }
        else
        {
            // ASCII character
            wstr[i++] = c;
        }
    }

    return wstr;
}