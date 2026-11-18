size_t count_string(char *s, char *e, int *flags)
{
 size_t len = e - s;
 size_t i = 1;
 int f = 0;
 unsigned char instring = 0;

 for (;;) {
  while (i + 8 <= len) {
   if (strtoksa[(unsigned char)(s[i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   if (strtoksa[(unsigned char)(s[++i])])
    goto tok;
   instring = 0;
   ++i;
  }
  while (i + 1 <= len) {
   if (strtoksa[(unsigned char)(s[i])])
    goto tok;
   instring = 0;
   ++i;
  }
  while (1) {
   if (s[i] == '"') {
    ++i;
    if (!instring)
     break;
    instring = 0;
    continue;
   }
   if (s[i] == '\\') {
    f |= 1;
    instring ^= 1;
   }
   ++i;
  }
  break;
 }
 *flags = f;
 return s + i;
tok:
 while (1) {
  if (s[i] == '"') {
   ++i;
   if (!instring)
    break;
   instring = 0;
   continue;
  }
  if (s[i] == '\\') {
   f |= 1;
   instring ^= 1;
  }
  ++i;
 }
 *flags = f;
 return s + i;
}