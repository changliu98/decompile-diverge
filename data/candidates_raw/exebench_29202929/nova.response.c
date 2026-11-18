static char *
func0(char *dst, const char *src)
{
    *dst = *src;
    while (*dst)
    {
        dst++;
        src++;
    }
    return dst;
}