char * func0(char * str, char ch, char newch)
{
    int i;

    strcpy(func0::str2, str);

    for (i = 0; i < strlen(func0::str2); i++)
        if (func0::str2[i] == ch)
            func0::str2[i] = newch;

    return func0::str2;
}