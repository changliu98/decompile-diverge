void str_replace(char *s,char oldchar,char newchar)
{
    char c;
    if (!s) return;
    while(1)
    {
        c = *s;
        if (!c) break;
        if (c == oldchar) *s = newchar;
        s++;
    }
}