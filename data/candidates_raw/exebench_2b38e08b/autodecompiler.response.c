void mystrncpy(char *s, char *t, int n)
{
    int i;
    for(i = 0; ; i++)
    {
        if((s[i] = (i < n ? t[i] : '\0')) == '\0')
            break;
    }
}