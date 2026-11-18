char * mystrcpy(char * dest, char * src)
{
    char *p = dest;
    while (*src)
        *(p++) = *(src++);
    *p = '\0';
    return dest;
}