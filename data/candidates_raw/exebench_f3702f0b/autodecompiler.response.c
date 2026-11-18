void escape(char s[], char t[])
{
    int i, j;
    for(i = 0, j = 0; t[j] != '\0'; i++, j++)
    {
        switch(t[i])
 {
     case ' ':
         s[j++] = '\\';
  s[j] = 'b';
  break;
     case '\n':
         s[j++] = '\\';
  s[j] = 'n';
  break;
     case '\t':
         s[j++] = '\\';
  s[j] = 't';
  break;
     default:
         s[j] = t[i];
  break;
 }
    }
    s[j] = '\0';
}