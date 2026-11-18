int is_anagram(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i; int j;
    for (i = 0; i < len1; i++)
    {
        int found = 0;
        for (j = 0; j < len2; j++)
        {
            if (s1[i] == s2[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            return 0;
        }
    }
    for (i = 0; i < len2; i++)
    {
        int found = 0;
        for (j = 0; j < len1; j++)
        {
            if (s2[i] == s1[j])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            return 0;
        }
    }
    return 1;
}