int func0(char *s)
{
    int i, j, k;
    int len = strlen(s);
    int count = 0;
    for(i = 0; i < len; i++)
    {
        for(j = 1; j <= len - i; j++)
        {
            if(check_Equality(s, i, i + j - 1))
                count++;
        }
    }
    return count;
}