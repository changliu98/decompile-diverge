void __cdecl replace_char(char *buf, char from, char to)
{
    for (; *buf; ++buf)
    {
        if (*buf == from)
            *buf = to;
    }
}