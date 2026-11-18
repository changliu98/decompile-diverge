static int wc_unescape(char *dest, char *src)
{
    char c;

    for (;;) {
 if (*src == '\0') {
     if (dest != NULL)
  *dest = '\0';
     c = 1;
     break;
 }
 switch (*src) {
 case '\\':
     src++;
     if (*src != '\0') {
  if (dest != NULL)
      *dest++ = *src;
  src++;
     }
     break;
 case '*':
 case '?':
 case '[':
 case ']':
     c = 0;
     goto done;
 default:
     if (dest != NULL)
  *dest++ = *src;
     src++;
     break;
 }
    }

done:
    return (c & 1);
}