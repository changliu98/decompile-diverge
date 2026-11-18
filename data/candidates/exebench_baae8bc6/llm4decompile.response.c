void reverse(char s[])
{
    char *i=s,*j=s;
    while(*j++)
        ;
    for(j-=2;i<j;i++,j--)
        *i=*i-*j,*j=*i+*j,*i=*j-*i;
}