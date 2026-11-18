int toml_value_string(const char *src, char **ret, int *len)
{
    int qchar;
    int srclen;
    const char *sp, *sq;
    int multiline = 0;


    *ret = NULL;


    if (!src)
        return -1;


    qchar = *src;
    srclen = strlen(src);
    if (qchar != '\'' && qchar != '"')
        return -1;


    if (src[1] == qchar && src[2] == qchar) {
        multiline = 1;
        sp = src + 3;
        sq = src + srclen - 3;
        if (sq < sp || *sq != qchar || *(sq - 1) != qchar || *(sq - 2) != qchar)
            return -1;


        if (*sp == '\n')
            sp++;
        else if (*sp == '\r' && *(sp + 1) == '\n')
            sp += 2;
    } else {
        sp = src + 1;
        sq = src + srclen - 1;
        if (sq < sp || *sq != qchar)
            return -1;
    }


    if (qchar == '\'')
        *ret = norm_lit_str(sp, sq - sp, len, multiline, NULL, 0);
    else
        *ret = norm_basic_str(sp, sq - sp, len, multiline, NULL, 0);

    if (*ret)
        return 0;
    else
        return -1;
}