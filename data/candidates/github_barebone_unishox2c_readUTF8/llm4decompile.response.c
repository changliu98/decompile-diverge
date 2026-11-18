unsigned int readUTF8(const char *buf, int len, int i, int *utf8len)
{
    unsigned int c = 0;

    if (i < len - 1 && (buf[i] & 0xE0) == 0xC0 && (buf[i + 1] & 0xC0) == 0x80)
    {
        c = ((buf[i] & 0x1F) << 6) + (buf[i + 1] & 0x3F);
        if (c >= 0x80)
        {
            *utf8len = 2;
            return c;
        }
    }

    if (i < len - 2 && (buf[i] & 0xF0) == 0xE0 && (buf[i + 1] & 0xC0) == 0x80 && (buf[i + 2] & 0xC0) == 0x80)
    {
        c = ((buf[i] & 0xF) << 12) + ((buf[i + 1] & 0x3F) << 6) + (buf[i + 2] & 0x3F);
        if (c >= 0x800)
        {
            *utf8len = 3;
            return c;
        }
    }

    if (i < len - 3 && (buf[i] & 0xF8) == 0xF0 && (buf[i + 1] & 0xC0) == 0x80 && (buf[i + 2] & 0xC0) == 0x80 && (buf[i + 3] & 0xC0) == 0x80)
    {
        c = ((buf[i] & 0x7) << 18) + ((buf[i + 1] & 0x3F) << 12) + ((buf[i + 2] & 0x3F) << 6) + (buf[i + 3] & 0x3F);
        if (c >= 0x10000)
        {
            *utf8len = 4;
            return c;
        }
    }

    return 0;
}