int func0(char *s)
{
    int i, j, len, count = 0;
    len = strlen(s);
    for(i = 0; i < len; i++)
    {
        for(j = 1; j <= len - i; j++)
        {
            if(check_Equality(s, i, j))
                count++;
        }
    }
    return count;
}