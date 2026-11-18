void reverse(char str[])
{
    int i,j,len;
    char c;
    for(len=0;str[len]!='\0';len++);
    for(i=0,j=len-1;i<len/2;i++,j--)
    {
        c=str[i];
        str[i]=str[j];
        str[j]=c;
    }
}