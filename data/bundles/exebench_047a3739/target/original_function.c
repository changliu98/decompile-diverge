void squeeze(char s1[], const char s2[])
{
 unsigned int i;
 unsigned int j;
 unsigned int k;

 for (i = j = 0; s1[j] != '\0'; j++) {
  for (k = 0; s2[k] != '\0' && s1[j] != s2[k]; k++)
   ;
  if (s2[k] == '\0')
   s1[i++] = s1[j];
 }
 s1[i] = '\0';
}