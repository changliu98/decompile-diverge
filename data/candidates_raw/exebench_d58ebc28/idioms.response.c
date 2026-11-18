void mystrcpy(char *str)
{
    char *str2 = "Goodbye";
    int i = 0;
    while (str[i])
    {
        str[i] = str2[i];
        i++;
    }
}