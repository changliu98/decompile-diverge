unsigned int __cdecl arikkei_ucs2_strncpy(const unsigned __int16 *s, unsigned __int16 *d, unsigned int maxlen)
{
    unsigned int i;

    for (i = 0; i < maxlen && *s != 0; ++i)
    {
        d[i] = *s++;
    }

    if (i < maxlen)
    {
        d[i] = 0;
    }

    return i;
}