int a2d(char ch)
{
    int ret;

    if (ch >= '0' && ch <= '9')
        ret = ch - '0';
    else if (ch >= 'a' && ch <= 'f')
        ret = ch - 'a' + 10;
    else if (ch >= 'A' && ch <= 'F')
        ret = ch - 'A' + 10;
    else
        ret = -1;

    return ret;
}