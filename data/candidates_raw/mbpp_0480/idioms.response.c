char get_max_char(char *str)
{
    int i; int j;
    int count[256];
    int max = -1;
    char max_char = '\0';
    int length = strlen(str);
    for (i = 0; i < length; i++)
    {
        count[(int)str[i]]++;
    }
    for (j = 0; j < length; j++)
    {
        if (count[(int)str[j]] > max)
        {
            max = count[(int)str[j]];
            max_char = str[j];
        }
    }
    return max_char;
}