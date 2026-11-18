char *func0(char *str1, char *result)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < strlen(str1); i++)
    {
        if (!(__ctype_b_loc()->values[(int)(str1[i])] & 0x2000))
        {
            result[j] = str1[i];
            j++;
        }
    }
    result[j] = '\0';
    return result;
}