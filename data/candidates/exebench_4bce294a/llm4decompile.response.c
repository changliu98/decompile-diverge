char *strichr(char *s, int c)
{
 char *t;

 if (s)
 {
  t = s;
  while (*t)
   t++;
  while (t >= s)
  {
   *(t+1) = *t;
   t--;
  }
  *s = c;
 }
 return s;
}