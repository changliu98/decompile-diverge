char read_escape_control_char(char c)
{
    if (c == 'n')
        return '\n';
    else if (c == 't')
        return '\t';
    else if (c == 'r')
        return '\r';
    else if (c == 'e')
        return 033; // '\e'
    else if (c == 'b')
        return '\b';
    else if (c == 'f')
        return '\f';
    else if (c == 'v')
        return '\v';
    else if (c == 'a')
        return '\a';
    return c;
}