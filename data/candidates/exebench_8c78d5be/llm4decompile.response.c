int enddata(char *buff, int p)
{
    int i;
    int offs;

    offs = p % 64;
    if (offs == 0)
        return 0;

    buff[p - offs + 1] = offs - 1;
    return p - offs + 64;
}