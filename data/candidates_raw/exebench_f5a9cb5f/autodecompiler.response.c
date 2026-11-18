void reverse(char s[])
{
    int c,i,j;
    for(i=0; s[i] != '\0'; i++)
        ;
    j=0;
    i--;
    while(j<i)
    {
        c=s[j];
        s[j]=s[i];
        s[i]=c;
        j++;
        i--;
    }
}