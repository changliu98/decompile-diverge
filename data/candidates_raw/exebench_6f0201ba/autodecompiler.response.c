void reverse(char s[])
{
    char c;
    int i, j, len;

    for(len = 0; s[len] != '\0'; ++len)
        ;

    for(i = 0; i < len/2; ++i)
    {
        c = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = c;
    }
}