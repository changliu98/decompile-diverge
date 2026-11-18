static char *parse_fmt(char *str, int *type, int *len)
{
 char *start = str;
 char *next;

 do {
  while (*str) {
   if (*str == '%' && *(str + 1) != '%') {
    break;
   }
   str++;
  }

  switch (*str) {
  case '%':
   switch (*(str + 1)) {
   case 'v':
    *type = 15;
    *len = str - start;
    next = str + 2;
    goto out;
   case '%':
    *len = str - start + 1;
    *type = -1;
    next = str + 2;
    goto out;
   }
  default:
   break;
  }
 } while (*str);

 *type = -1;
 *len = str - start;
 next = str;

out:
 return next;
}