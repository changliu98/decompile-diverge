int func0(char *str)
{
    int i, count;
    char *vowel = "AEIOU";

    for (i = 0, count = 0; str[i] && i * 2 < strlen(str); i++)
        if (strchr(vowel, str[i * 2]))
            count++;

    return count;
}