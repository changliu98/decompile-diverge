int is_uletter(int c)
{
    int ret = 0;
    if (c >= 'A')
        ret = c <= 'Z';
    return ret;
}