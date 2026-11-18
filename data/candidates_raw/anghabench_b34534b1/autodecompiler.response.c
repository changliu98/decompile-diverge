static char *
get_base(char *str, int *base)
{
 char *p;

 if (*str == '0') {
  switch (*(str + 1)) {
  case 'x':
   *base = 16;
   break;
  case 't':
  case 'n':
   *base = 10;
   break;
  case 'o':
   *base = 8;
   break;
  default:
   *base = 10;
   p = str;
   break;
  }
  p = str + 2;
 } else {
  *base = 10;
  p = str;
 }
 return (p);
}