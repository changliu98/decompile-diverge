void charset_remove(char *buffer, char value)
{
    char *r = buffer;
    char *l = buffer;

    while (*r != 0)
    {
        if (*r != value)
        {
            *l = *r;
            l++;
        }
        r++;
    }
    *l = 0;
}