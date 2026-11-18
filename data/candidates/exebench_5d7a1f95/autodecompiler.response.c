void escape(char s[], char t[])
{
    int i, j;
    for(i = 0, j = 0; t[j] != '\0'; i++, j++)
    {
        switch(t[i])
 {
     case '\a':
         s[j] = '\\';
  s[++j] = 'a';
  break;
     case '\b':
         s[j] = '\\';
  s[++j] = 'b';
  break;
     case '\f':
         s[j] = '\\';
  s[++j] = 'f';
  break;
     case '\n':
         s[j] = '\\';
  s[++j] = 'n';
  break;
     case '\r':
         s[j] = '\\';
  s[++j] = 'r';
  break;
     case '\t':
         s[j] = '\\';
  s[++j] = 't';
  break;
     case '\v':
         s[j] = '\\';
  s[++j] = 'v';
  break;
     case '\\':
         s[j] = '\\';
  s[++j] = '\\';
  break;
     case '\?':
         s[j] = '\\';
  s[++j] = '?';
  break;
     case '\'':
         s[j] = '\\';
  s[++j] = '\'';
  break;
     case '\"':
         s[j] = '\\';
  s[++j] = '\"';
  break;
     default:
         s[j] = t[i];
 }
    }
    s[j] = '\0';
}