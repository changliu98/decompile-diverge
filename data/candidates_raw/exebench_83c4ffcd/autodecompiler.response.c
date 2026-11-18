char *get_line(char *s,char *l,int c)
{
 char *b;
 int i;

 b = l;
 i = 0;
 for(;;)
 {
  if ((i >= (c-1)) || (*b == '\0') ||
      (*b == '\n') || (*b == '\r'))
  {
   *s = '\0';
   break;
  }
  *s++ = *b++;
  i++;
 }
 if (*b == '\r')
  b++;
 if (*b == '\n')
  b++;
 return(b);
}