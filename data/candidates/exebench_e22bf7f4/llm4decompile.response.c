void reverse(char s[])
{
    int i,j,len;
    char c;
    for(i=0;s[i]!='\0';i++)
    {
        len=i+1;
    }
    for(i=0,j=len-1;i<len/2;i++,j--)
    {
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}