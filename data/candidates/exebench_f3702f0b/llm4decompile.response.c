void escape(char *s, char *t)
{
 int i, j;

 for (i = 0, j = 0; t[i] != '\0'; i++) {
  if (t[i] == '\t') {
   s[j++] = '\\';
   s[j++] = 't';
  } else if (t[i] == '\n') {
   s[j++] = '\\';
   s[j++] = 'n';
  } else if (t[i] == ' ') {
   s[j++] = '\\';
   s[j++] = 'b';
  } else {
   s[j++] = t[i];
  }
 }
 s[j] = '\0';
}