void reverse(char *s) {
 char *e = s, *b = s, c;
 while (*e++)
  ;
 e -= 2;

 while (b < e) {
  c = *b;
  *b = *e;
  *e = c;
  e--;
  b++;
 }
}