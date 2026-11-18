void reverse(char s[])
{
    int i,j,k;
    char c;

    for(i=0; s[i]!='\0' && s[i]!='\n'; ++i)
        ;

    for(j=0,k=i-1; j<k; ++j,--k)
    {
        c = s[j];
        s[j] = s[k];
        s[k] = c;
    }
}