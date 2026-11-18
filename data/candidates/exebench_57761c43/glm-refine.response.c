void __cdecl char_replace(char *str, char origc, char newc)
{
    char *v3;

    while (*str)
    {
        v3 = str++;
        if (*str == origc)
            *str = newc;
    }
}