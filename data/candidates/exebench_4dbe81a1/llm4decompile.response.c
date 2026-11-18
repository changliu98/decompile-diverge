char *GO_strcpy (char *d, char *s)
{
 char *tmp = d;

 for (;;) {
  if (!(*d++ = *s++))
   break;
 }
 return tmp;
}