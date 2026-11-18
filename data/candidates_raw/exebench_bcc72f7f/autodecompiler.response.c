void modify_string(char str[100], int n)
{
    int i,k,m;
    for(i=0; str[i]!=0;++i)
    {
        if(str[i]=='-')
        {
            str[i]=' ';
        }
        else
        {
            k=str[i]-'a';
            m=(k+n%26)%26;
            str[i]=m+'a';
        }
    }
}