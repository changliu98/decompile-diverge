void replaceChar(char *s,char oldc,char newc)
{
    if(s==NULL)
        return;

    while(*s!='\0')
    {
        if(*s==oldc)
            *s=newc;
        s++;
    }
}