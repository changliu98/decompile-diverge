void escape(char s[], char t[])
{
    int i,j;
    for(i=0,j=0;;i++,j++)
    {
        switch(s[i])
        {
            case '\n':
                s[j++]='\\';
                s[j]='n';
                break;
            case '\t':
                s[j++]='\\';
                s[j]='t';
                break;
            default:
                if(s[i]=='\0'||t[j]=='\0')
                    return;
                s[j]=t[j];
                break;
        }
    }
}