int get_num(char *s, int *n)
{
 int c;
 int base = 10;
 int i = 0;
 int status;

 *n = 0;
 if ((s[0] == '0') && (s[1] == 'x')) {
  i = 2;
  base = 16;
 }
 if (s[i] == '\0') return(-1);
 for (;;) {
  if (s[i] == '\0') {
   status = 0;
   break;
  }
  if ((c = s[i]) >= '0' && c <= '9')
   c -= '0';
  else if (base == 16 && c >= 'A' && c <= 'F')
   c = c - 'A' + 10;
  else if (base == 16 && c >= 'a' && c <= 'f')
   c = c - 'a' + 10;
  else {
   status = -1;
   break;
  }
  *n = (*n) * base + c;
  i++;
 }
 return(status);
}