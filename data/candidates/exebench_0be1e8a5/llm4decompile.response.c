void short_to_string(char *res, unsigned short s)
{
    res[0] = s / 10000 + '0';
    s %= 10000;
    res[1] = s / 1000 + '0';
    s %= 1000;
    res[2] = s / 100 + '0';
    s %= 100;
    res[3] = s / 10 + '0';
    s %= 10;
    res[4] = s + '0';
    res[5] = '\0';
}