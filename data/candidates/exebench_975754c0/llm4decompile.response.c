void reverse(char s[])
{
    int i,j,k;
    char c;
    for(i=0;s[i]!='\0';i++);
    for(j=0,k=i-1;j<i/2;j++,k--)
    {
        c=s[j];
        s[j]=s[k];
        s[k]=c;
    }
}