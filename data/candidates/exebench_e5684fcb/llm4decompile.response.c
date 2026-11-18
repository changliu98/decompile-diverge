int reverse(char s[])
{
    char *i=s,*j=s;
    while(*j++)
        ;
    j-=2;
    while(i<j)
        *i++=*i^*j,
        *j--=*i^*j,
        *i++=*i^*j;
    return 0;
}