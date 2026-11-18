char *strcpyend(char *to, const char *from)
{
    while ((*to++ = *from++));
    return --to;
}