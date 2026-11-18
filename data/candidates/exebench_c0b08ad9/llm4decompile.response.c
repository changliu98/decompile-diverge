void escape(char *s, char *t)
{
 int i = 0;
 int j = 0;

 while (s[i] != '\0' && t[j] != '\0') {
  if (t[j] == '\t') {
   s[i++] = '\\';
   s[i++] = 't';
   j++;
  } else if (t[j] == '\n') {
   s[i++] = '\\';
   s[i++] = 'n';
   j++;
  } else {
   s[i++] = t[j++];
  }
 }
}