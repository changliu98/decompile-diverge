void modify_string(char str[100], char n)
{
    int i=0,j=0;
    for(i=0;str[i]!='\0';i++)
    {
        if((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z'))
        {
            j=0;
            while(j<n)
            {
                if(str[i]=='Z')
                str[i]='A';

                if(str[i]=='z')
                str[i]='a';

                str[i]++;
                j++;
            }
        }
    }
}