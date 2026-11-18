void strrev(char s[])
{
    int i,j,len;
    char c;
    for(len=0;s[len]!='\0';len++);
    for(i=0,j=len-1;i<j;i++,j--)
    {
        c=s[j];
        s[j]=s[i];
        s[i]=c;
    }
}