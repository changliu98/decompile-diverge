void unhide(char text[1000])
{
    int i,k;
    char klucz[3] = {3,5,7};
    for(i=0,k=0;text[i]!='\0';i++,k++)
    {
        text[i]-=klucz[k];
        if(k==2)
            k=-1;
    }
}