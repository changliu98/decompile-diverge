void reverse(char *s) {
 char *e = s;
 while (*e)
  e++;
 while (s < e) {
  int t = *s;
  *s++ = *e--;
  *e = t;
 }
}