
static char *
read_int(char *s, int nr, int *d)
{
    int result = 0;

    while (--nr >= 0 && *s >= '0' && *s <= '9')
 result = result * 10 + (*s++ - '0');

    *d = result;
    return (s);
}
