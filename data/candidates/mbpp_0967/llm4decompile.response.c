char* func0(char* str)
{
    static const char s_AEIOUaeiou[] = "AEIOUaeiou";
    int found[10];
    int count = 0;
    int i, j;

    memset(found, 0, sizeof(found));

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (str[i] == s_AEIOUaeiou[j] && !found[j])
            {
                found[j] = 1;
                count++;
                break;
            }
        }
    }

    return (count >= 5) ? "accepted" : "not accepted";
}