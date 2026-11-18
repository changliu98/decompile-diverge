int func0(char *str)
{
    int length = 0;
    while (*str++)
        length++;
    return length;
}