int SSL_select_next_proto(char **ret, unsigned char *retlen, char *haystack, unsigned int haystacklen, char *needle, unsigned int needlelen)
{
    unsigned int i, j;
    unsigned char *p;
    int found = 0;

    for (i = 0; i < haystacklen; i++)
    {
        for (j = 0; j < needlelen; j++)
        {
            if ((unsigned char)haystack[i] == (unsigned char)needle[j])
            {
                if (!memcmp(&haystack[i + 1], &needle[j + 1], (unsigned char)haystack[i]))
                {
                    p = (unsigned char *)&haystack[i];
                    found = 1;
                    goto end_for;
                }
            }

            j += (unsigned char)needle[j];
        }

        i += (unsigned char)haystack[i];
    }

    p = (unsigned char *)needle;
    found = 2;

end_for:

    *ret = (char *)p + 1;
    *retlen = *p;

    return found;
}