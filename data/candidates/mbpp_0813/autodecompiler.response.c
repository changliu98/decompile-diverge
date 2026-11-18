int func0(char *s)
{
 int l = 0;
 while (1) {
  if (*s == 0)
   return l;
  l++;
  s++;
 }
}