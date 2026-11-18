void inplace_strcpy(char *to, char *from)
{
    while (*from)
        *(to++) = *(from++);
    *to = 0;
}