char *fix(char *dest, char *src)
{
 int i;
 int j;

 i = 0;
 j = 0;
 while (1)
 {
  if (src[i] == '\0')
  {
   dest[j] = '\0';
   return (dest);
  }
  if (src[i] == '\b')
  {
   j--;
   if (j < 0)
    j = 0;
  }
  else
   dest[j++] = src[i];
  i++;
 }
}