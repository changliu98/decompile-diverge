char *stb_skipnewline(char *s)
{
   if (*s == '\r' || *s == '\n')
      ++s;
   if (s[0] == '\r' && s[1] == '\n')
      ++s;
   return s;
}