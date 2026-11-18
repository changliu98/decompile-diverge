void squeeze(char s1[], char s2[])
{
    int i, j, k;
    char *p2;
    char *p1 = s1;
    char *p3 = p1;

    for (; *s1 != '\0'; s1++)
    {
        p2 = s2;
        int skip = 0;
        for (; *p2 != '\0'; p2++)
            if (*s1 == *p2)
            {
                skip = 1;
                break;
            }
        if (skip)
            continue;
        else
            *p3++ = *s1++;
    }
    *p3 = '\0';
}