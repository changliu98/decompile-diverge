int func0(char *str)
{
    int i = 0;
    while(*str != '\0')
    {
        i++;
        str++;
    }
    return i;
}