int func0(char str1[])
{
    int i;
    int top=-1;
    char stack[100];
    char parenthese;
    for(i=0;i<strlen(str1);i++)
    {
        if(str1[i]=='('||str1[i]=='{'||str1[i]=='[')
        {
            stack[top+1]=str1[i];
            top++;
        }
        else
        {
            if(top==-1)
            {
                return 0;
            }
            else
            {
                parenthese=stack[top];
                top--;
                if((str1[i]==')'&&parenthese!='(')||(str1[i]=='}'&&parenthese!='{')||(str1[i]==']'&&parenthese!='['))
                {
                    return 0;
                }
            }
        }
    }
    if(top==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}