static int
escape(char *str, int percent, size_t *len)
{
 char *p, *s, c;
 int i, octal, done;

 p = s = str;
 for (;;) {
  c = *str;
  if (c == '\0') {
   *p = '\0';
   *len = p - s;
   return (0);
  }
  switch (c) {
  case '\\':
   c = *++str;
   switch (c) {
   case '\0':
    *p++ = '\\'; *p = '\0';
    *len = p - s;
    return (0);
   case '\\':
   case '\'':
    *p = *str;
    break;
   case 'a':
    *p = '\a';
    break;
   case 'b':
    *p = '\b';
    break;
   case 'c':
    if (!percent) {
     *p = '\0';
     *len = p - s;
     return (1);
    }
    *p = 'c';
    break;
   case 'f':
    *p = '\f';
    break;
   case 'n':
    *p = '\n';
    break;
   case 'r':
    *p = '\r';
    break;
   case 't':
    *p = '\t';
    break;
   case 'v':
    *p = '\v';
    break;
   case '0': case '1': case '2': case '3':
   case '4': case '5': case '6': case '7':
    c = (char)((percent) ? 4 : (*str == '0'));
    c = (char)((c & 1) ? 4 : 3);
    i = 0;
    while ((c-- != 0) && (*str >= '0') && (*str <= '7')) {
     i *= 8;
     i += *str - '0';
     ++str;
    }
    --str;
    if (percent && (i == '%')) {
     *p++ = '%';
     *p = '%';
    } else
     *p = (char)i;
    break;
   default:
    *p = *str;
   }
   break;
  default:
   *p = c;
  }
  ++str;
  ++p;
 }
}