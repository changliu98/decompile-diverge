int stringToInt(int *i, char *s)
{
 int err;

 *i = 0;
 for (;;) {
  switch (*s) {
  case '\0':
   err = 0;
   break;
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
   *i = ((*i)*10)+(*s)-'0';
   s++;
   continue;
  default:
   err = -1;
   break;
  }
  return err;
 }
}