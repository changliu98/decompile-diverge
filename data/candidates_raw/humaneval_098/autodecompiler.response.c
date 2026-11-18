int vowelCounter(char *str)
{
    char *vowels = "AEIOU";
    int counter = 0;
    for(int i = 0; str[i] != '\0' && i < strlen(str); i++)
        if(strchr(vowels, str[i]) != NULL)
            counter++;
    return counter;
}