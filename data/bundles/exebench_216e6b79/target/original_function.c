void unescape(char s[], char t[])
{
 int i, j;

 i = j = 0;
 while (t[i] != '\0') {
  switch (t[i]) {
  case '\\':
   ++i;
   switch (t[i]) {
   case 'a':
    s[j] = '\a';
    break;
   case 'b':
    s[j] = '\b';
    break;
   case 'f':
    s[j] = '\f';
    break;
   case 'n':
    s[j] = '\n';
    break;
   case 'r':
    s[j] = '\r';
    break;
   case 't':
    s[j] = '\t';
    break;
   case 'v':
    s[j] = '\v';
    break;
   case '?':
    s[j] = '\?';
    break;
   case '\\':
    s[j] = '\\';
    break;
   case '\'':
    s[j] = '\'';
    break;
   case '\"':
    s[j] = '\"';
    break;
   default:
    s[j] = '\\';
    ++j;
    s[j] = t[i];
   }
   break;
  default:
   s[j] = t[i];
   break;
  }
  ++i;
  ++j;
 }
 s[j] = '\0';
}