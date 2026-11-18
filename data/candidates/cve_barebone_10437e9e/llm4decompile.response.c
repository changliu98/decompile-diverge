BITCODE_TU bit_utf8_to_TU(char *str, int cquoted)
{
    size_t i, j, len;
    unsigned short *wstr;
    unsigned char *ustr;
    unsigned char c;
    int cquoted_local;

    ustr = (unsigned char *)str;
    len = strlen(str);
    if (len > 65535 -1)
    {
        len = 65535 -1;
        loglevel = 1;
    }
    wstr = calloc(2, len + 1);
    if (wstr == NULL)
    {
        loglevel = 1;
        return NULL;
    }
    for (i = 0, j = 0; len > 0; len--)
    {
        c = *ustr++;
        if (c < 0x80)
        {
            cquoted_local = (cquoted && (c == '\\') && (len > 1));
            if (cquoted_local && (*ustr == '\\' || *ustr == '"' || *ustr == 'r' || *ustr == 'n'))
            {
                c = *ustr++;
                if (c == 'r')
                    wstr[j++] = '\r';
                else if (c == 'n')
                    wstr[j++] = '\n';
                else
                    wstr[j++] = c;
            }
            else
                wstr[j++] = c;
        }
        else if ((c & 0xe0) == 0xc0)
        {
            if (len > 0)
            {
                wstr[j++] = ((c & 0x1f) << 6) | (*ustr & 0x3f);
                ustr++;
                len--;
            }
        }
        else if ((c & 0xf0) == 0xe0)
        {
            if (len > 1)
            {
                wstr[j++] = ((c & 0x0f) << 12) | ((*ustr++ & 0x3f) << 6) | (*ustr & 0x3f);
                len -= 2;
            }
        }
    }
    return (BITCODE_TU)wstr;
}