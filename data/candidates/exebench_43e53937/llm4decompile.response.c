void Utf32toUtf8(unsigned int codepoint, char *utf8Buf)
{
    if (codepoint <= 0x7f)
    {
        utf8Buf[0] = (char)codepoint;
        utf8Buf[1] = '\0';
    }
    else if (codepoint <= 0x7ff)
    {
        utf8Buf[0] = (char)(0xc0 | (codepoint >> 6));
        utf8Buf[1] = (char)(0x80 | (codepoint & 0x3f));
        utf8Buf[2] = '\0';
    }
    else if (codepoint <= 0xffff)
    {
        utf8Buf[0] = (char)(0xe0 | (codepoint >> 12));
        utf8Buf[1] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
        utf8Buf[2] = (char)(0x80 | (codepoint & 0x3f));
        utf8Buf[3] = '\0';
    }
    else if (codepoint <= 0x1fffff)
    {
        utf8Buf[0] = (char)(0xf0 | (codepoint >> 18));
        utf8Buf[1] = (char)(0x80 | ((codepoint >> 12) & 0x3f));
        utf8Buf[2] = (char)(0x80 | ((codepoint >> 6) & 0x3f));
        utf8Buf[3] = (char)(0x80 | (codepoint & 0x3f));
        utf8Buf[4] = '\0';
    }
    else
    {
        utf8Buf[0] = '?';
        utf8Buf[1] = '\0';
    }
}