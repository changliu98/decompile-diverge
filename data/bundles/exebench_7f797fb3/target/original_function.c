char * strcpy(char * dst, const char *src)
{
    char * tmp = dst;
    while(((*tmp++) = (*src++)));
    return dst;
}