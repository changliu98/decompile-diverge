void
dopr_outch(
    char *buffer,
    size_t *currlen,
    size_t maxlen,
    int c)
{
    if (*currlen < maxlen)
        buffer[*currlen] = (char)c;
    (*currlen)++;
    return;
}