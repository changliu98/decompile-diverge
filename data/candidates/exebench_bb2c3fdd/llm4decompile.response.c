void reverse(char s[])
{
    int i,j,length;
    char c;
    for(length=0;s[length]!='\0';length++);
    for(i=0,j=length-1;i<=length/2-1;i++,j--){
        c=s[i];
        s[i]=s[j];
        s[j]=c;
    }
}