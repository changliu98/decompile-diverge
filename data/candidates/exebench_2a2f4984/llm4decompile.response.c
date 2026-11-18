int cpy(char *a,char *b)
{
    int i;
    for(i=0;b[i]!='\0'&&i<100;i++)
        a[i]=b[i];
    a[i]='\0';
    return 0;
}