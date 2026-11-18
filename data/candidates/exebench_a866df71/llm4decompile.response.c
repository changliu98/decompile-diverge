char *skip(char *s, char c)
{
 while (*s == c || *s)
  if (*s)
   s++;
  else
   break;
 if (*s)
  *s++ = 0;
 return s;
}