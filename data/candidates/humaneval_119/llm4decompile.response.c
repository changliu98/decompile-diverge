char* func0(char s1[],char s2[])
{
    int i,j,flag,count,len1,len2;
    count = 0;
    flag = 1;
    len1 = strlen(s1);
    len2 = strlen(s2);
    for(i=0;i<len1;i++)
    {
        if(s1[i]=='(')
            count++;
        if(s1[i]==')')
            count--;
        if(count<0)
            flag = 0;
    }
    for(i=0;i<len2;i++)
    {
        if(s2[i]=='(')
            count++;
        if(s2[i]==')')
            count--;
        if(count<0)
            flag = 0;
    }
    if(count==0 && flag)
        return "Yes";
    count = 0;
    flag = 1;
    for(i=0;i<len2;i++)
    {
        if(s2[i]=='(')
            count++;
        if(s2[i]==')')
            count--;
        if(count<0)
            flag = 0;
    }
    for(i=0;i<len1;i++)
    {
        if(s1[i]=='(')
            count++;
        if(s1[i]==')')
            count--;
        if(count<0)
            flag = 0;
    }
    if(count==0 && flag)
        return "Yes";
    return "No";
}