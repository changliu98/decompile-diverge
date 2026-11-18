void wdc_UtilsDeleteCharFromString(char *str, int strSize, char charToRemove)
{
    int i; int j = 0;
    int isChar = 0;
    if (str == ((void *)0) || strSize == 0)
        return;
    for (i = 0; (isChar = (i < strSize ? (str[i] != '\0') : 0)) != 0; i++)
    {
        if (str[i] == charToRemove)
            continue;
        str[j++] = str[i];
    }
    str[j] = '\0';
}