char *__cdecl func0(char *str)
{
    int len = strlen(str);
    int j = 0;
    
    for (int i = 0; i < len; ++i)
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
    }
    
    str[j] = '\0';
    return str;
}