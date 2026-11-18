void reverse(char *s) {
 char *e = s;
 while (*s)
  s++;
 s--;
 while (e < s) {
  char t = *e;
  *e = *s;
  *s = t;
  e++;
  s--;
 }
}