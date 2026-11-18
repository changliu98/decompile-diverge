char *__cdecl strcpy(char *dst, const char *src)
{
    size_t i = 0;
    
    do 
    {
        dst[i] = src[i];
    } 
    while (src[i++]);

    return dst;
}