int func0(char *s)
{
    int i, length, count;
    char *vowels = "aeiouAEIOU";

    count = 0;
    length = strlen(s);

    for(i = 0; i < length; i++)
    {
        if(strchr(vowels, s[i]))
            count++;
    }

    if(length > 0 && (s[length - 1] == 'y' || s[length - 1] == 'Y'))
        count++;

    return count;
}