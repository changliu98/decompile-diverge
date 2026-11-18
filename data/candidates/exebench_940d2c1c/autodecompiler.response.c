void escape(char s[], char t[])
{
    int i, j;
    for(i = 0, j = 0; t[j] != '\0'; i++, j++)
    {
        switch(t[i])
 {
     case '\n':
         s[j++] = '\\';
  s[j] = 'n';
  break;
     case '\t':
         s[j++] = '\\';
  s[j] = 't';
  break;
     case '\\':
         s[j++] = '\\';
  s[j] = '\\';
  break;
     case '"':
         s[j++] = '\\';
  s[j] = '"';
  break;
     default:
         s[j] = t[i];
 }
    }
    s[j] = t[i];
}