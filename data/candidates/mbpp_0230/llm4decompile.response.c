char * func0(char * str1, char * char_replacement)
{
    int i = 0;
    int j = 0;
    while (str1[i] != '\0')
    {
        if (str1[i] == ' ')
        {
            func0::str2[j] = char_replacement[0];
        }
        else
        {
            func0::str2[j] = str1[i];
        }
        i++;
        j++;
    }
    func0::str2[j] = '\0';
    return func0::str2;
}