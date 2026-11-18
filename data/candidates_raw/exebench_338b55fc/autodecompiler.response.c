void reverse(char *s) {
 char *e = s, *b = s;
 while (*e != '\0') e++;
 e--;
 while (b < e) {
  *b ^= *e;
  *e ^= *b;
  *b ^= *e;
  b++;
  e--;
 }
}