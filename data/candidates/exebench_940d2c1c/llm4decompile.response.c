void escape(char *s1, char *s2)
{
 int i, j;

 i = j = 0;
 while (s2[i] != '\0') {
  if (s2[i] == '\t') {
   s1[j++] = '\\';
   s1[j++] = 't';
  } else if (s2[i] == '\n') {
   s1[j++] = '\\';
   s1[j++] = 'n';
  } else if (s2[i] == '"') {
   s1[j++] = '\\';
   s1[j++] = '"';
  } else if (s2[i] == '\\') {
   s1[j++] = '\\';
   s1[j++] = '\\';
  } else {
   s1[j++] = s2[i];
  }
  i++;
 }
 s1[j] = s2[i];
}