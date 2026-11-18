void reverse(char *str)
{
    int i; int j;
    char tmp;
    for (i = 0; (str[i] != '\0') && (str[i] != '\n'); i++)
    {
    }
    j = i - 1;
    for (i = 0; i < j; i++)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        j--;
    }
}