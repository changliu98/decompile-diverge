int cpy(char a[100],char b[100])
{
    int i;
    for(i=0; b[i]!='\0'&&i<100; i++)
        a[i]=b[i];
    a[i]='\0';
    return 0;
}