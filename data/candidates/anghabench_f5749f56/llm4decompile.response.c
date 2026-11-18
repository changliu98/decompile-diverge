int hex2int(int ch)
{
    int i;

    if (ch >= 'a' && ch <= 'f')
        i = ch - 'a' + 10;
    else if (ch >= 'A' && ch <= 'F')
        i = ch - 'A' + 10;
    else
        i = ch - '0';

    return i;
}