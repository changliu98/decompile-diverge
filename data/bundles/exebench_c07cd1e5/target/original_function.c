void replaceChar(char *s, char oldc, char newc)

{
if (!s)
    return;
char c;
while((c=*s))
    {
    if (c == oldc)
       *s = newc;
    ++s;
    }
}