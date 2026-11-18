char * func0(char * text)
{
    int i = 0;
    int j = 0;
    char temp[strlen(text) + 1];

    while (text[i] != '\0')
    {
        if ( isspace(text[i]) )
        {
            temp[j] = text[i];
            j++;
        }
        i++;
    }
    temp[j] = '\0';

    strcpy(text, temp);

    return text;
}