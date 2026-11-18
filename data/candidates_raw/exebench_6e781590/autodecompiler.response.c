void str_replace(char *s,char oldchar,char newchar)
{
    while(1)
    {
        if(*s==0)break;
        if(*s==oldchar)*s=newchar;
        s++;
    }
}