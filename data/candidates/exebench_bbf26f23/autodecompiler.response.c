char *strcpy(char *s1, char *s2)
{
 int i;

 i = 0;
 while (1)
 {
  if (s2[i] == '\0')
  {
   s1[i] = '\0';
   return (s1);
  }
  s1[i] = s2[i];
  i++;
 }
}