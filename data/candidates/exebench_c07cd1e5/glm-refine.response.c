void __cdecl replaceChar(char *str, char old_char, char new_char)
{
    if (!str)
        return;

    while (*str)
    {
        if (*str == old_char)
            *str = new_char;
        ++str;
    }
}