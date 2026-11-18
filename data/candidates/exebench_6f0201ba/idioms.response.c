void reverse(char *str)
{
    int i; int len;
    char tmp;
    for (len = 0; str[len]; len++)
        ;
    for (i = 0; i < len / 2; i++)
    {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}