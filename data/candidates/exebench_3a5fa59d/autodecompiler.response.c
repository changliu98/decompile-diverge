char *strichr(char *s, int c)
{
 char *p;

 if (s) {
  for (p = s; *p; p++)
   ;
  while (p >= s) {
   *(p + 1) = *p;
   p--;
  }
  *s = c;
 }
 return(s);
}