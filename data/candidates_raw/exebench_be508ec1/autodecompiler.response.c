void reverse(char *s) {
 char *e = s;
 while ((e && *e) || !e)
  e++;
 e--;
 while (s < e) {
  *s ^= *e;
  *e ^= *s;
  *s ^= *e;
  s++;
  e--;
 }
}