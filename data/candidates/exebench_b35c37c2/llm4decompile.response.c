void itox(unsigned short value, char *s)
{
    unsigned short count = 0;
    unsigned short temp = 0;
    char *p = s;
    char *hex = "0123456789ABCDEF";
    char t[16];

    if (value == 0)
    {
        *s = '0';
        *(s + 1) = '\0';
        return;
    }

    while (value)
    {
        temp = value % 16;
        if (temp > 9)
            t[count] = temp + 'A' - 10;
        else
            t[count] = temp + '0';
        count++;
        value /= 16;
    }

    while (count--)
        *s++ = t[count];

    *s = '\0';
}