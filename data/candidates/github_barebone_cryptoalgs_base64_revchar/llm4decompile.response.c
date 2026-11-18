char
revchar(char c)
{
    if (c >= 'A' && c <= 'Z')
	c = 'Z' - (c - 'A');
    else if (c >= 'a' && c <= 'z')
	c = 'z' - (c - 'a');
    else if (c >= '0' && c <= '9')
	c = '9' - (c - '0');
    else if (c == '+')
	c = '>';
    else if (c == '/')
	c = '?';
    return c;
}