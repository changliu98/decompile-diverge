
static void gdb_strcpy(char *buf, const char *s)
{
    while (*s)
        *buf++ = *s++;
    *buf = 0;
}
