int __cdecl unicode_to_utf8(char *buf, unsigned int c)
{
    char *ptr = buf;

    if (c < 0x80)
    {
        *ptr++ = c;
    }
    else if (c < 0x800)
    {
        *ptr++ = (c >> 6) | 0xC0;
        *ptr++ = (c & 0x3F) | 0x80;
    }
    else if (c < 0x10000)
    {
        *ptr++ = (c >> 12) | 0xE0;
        *ptr++ = (c >> 6) & 0x3F | 0x80;
        *ptr++ = (c & 0x3F) | 0x80;
    }
    else if (c < 0x200000)
    {
        *ptr++ = (c >> 18) | 0xF0;
        *ptr++ = (c >> 12) & 0x3F | 0x80;
        *ptr++ = (c >> 6) & 0x3F | 0x80;
        *ptr++ = (c & 0x3F) | 0x80;
    }
    else if (c < 0x4000000)
    {
        *ptr++ = (c >> 24) | 0xF8; // IDA decompiled this as HIBYTE(c) | 0xF8
        *ptr++ = (c >> 18) & 0x3F | 0x80;
        *ptr++ = (c >> 12) & 0x3F | 0x80;
        *ptr++ = (c >> 6) & 0x3F | 0x80;
        *ptr++ = (c & 0x3F) | 0x80;
    }
    else
    {
        *ptr++ = (c >> 30) | 0xFC;
        *ptr++ = (c >> 24) & 0x3F | 0x80; // IDA decompiled this as HIBYTE(c) & 0x3F | 0x80
        *ptr++ = (c >> 18) & 0x3F | 0x80;
        *ptr++ = (c >> 12) & 0x3F | 0x80;
        *ptr++ = (c >> 6) & 0x3F | 0x80;
        *ptr++ = (c & 0x3F) | 0x80;
    }

    *ptr = 0; // Null-terminate the string
    return (int)(ptr - buf);
}