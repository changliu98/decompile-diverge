int __cdecl u_get(int *up, const char *s)
{
    unsigned char c = (unsigned char)*s;

    // ASCII character (0xxxxxxx)
    if (c < 0x80)
    {
        *up = c;
        return 1;
    }

    // Invalid UTF-8 leading byte (10xxxxxx or 11111111/11111110)
    if (c < 0xC0 || c >= 0xFE)
    {
        return 0;
    }

    // Multi-byte UTF-8 sequences
    if (c < 0xE0)
    {
        // 2-byte sequence (110xxxxx 10xxxxxx)
        *up = ((c & 0x1F) << 6) | (s[1] & 0x3F);
        if ((*up & 0xFFFFFF80) != 0)
            return 2;
        return 0;
    }
    else if (c < 0xF0)
    {
        // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        *up = ((c & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        if ((*up & 0xFFFFF800) != 0)
            return 3;
        return 0;
    }
    else if (c < 0xF8)
    {
        // 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        *up = ((c & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
        if ((*up & 0xFFFF0000) != 0)
            return 4;
        return 0;
    }
    else if (c < 0xFC)
    {
        // 5-byte sequence (111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx)
        *up = ((c & 0x03) << 24) | ((s[1] & 0x3F) << 18) | ((s[2] & 0x3F) << 12) | ((s[3] & 0x3F) << 6) | (s[4] & 0x3F);
        if ((*up & 0xFFE00000) != 0)
            return 5;
        return 0;
    }
    else
    {
        // 6-byte sequence (1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx)
        *up = ((c & 0x01) << 30) | ((s[1] & 0x3F) << 24) | ((s[2] & 0x3F) << 18) | ((s[3] & 0x3F) << 12) | ((s[4] & 0x3F) << 6) | (s[5] & 0x3F);
        if ((*up & 0xFC000000) != 0)
            return 6;
        return 0;
    }
}