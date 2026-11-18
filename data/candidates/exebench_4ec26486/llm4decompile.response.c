void squeeze_all(char s[], char b[])
{
 int i, j, k;
 int c;
 int badchar;

 k = 0;
 for (i = 0; s[i] != '\0'; i++) {
  badchar = 0;
  for (j = 0; b[j] != '\0'; j++) {
   if (s[i] == b[j])
    badchar = 1;
  }
  if (!badchar)
   s[k++] = s[i];
 }
 s[k] = '\0';
}