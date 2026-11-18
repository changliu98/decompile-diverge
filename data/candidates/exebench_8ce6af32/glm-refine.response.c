bool __cdecl endStrider(const char *s, int *addend)
{
    *addend = 0;
    return strstr(s, "//") != NULL;
}