int scan_8long(const char *s,long *result)
{
    register long value = 0;
    register int digit;
    register int pos = 0;

    while ((digit = s[pos] - '0') >= 0 && digit <= 7)
    {
        value = (value << 3) + digit;
        pos++;
    }

    *result = value;
    return pos;
}