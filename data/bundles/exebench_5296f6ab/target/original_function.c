static void
charset_remove(char buffer[], char value)
{
 char *l = buffer;
 const char *r = buffer;
 while(*r != '\0')
 {
  if(*r != value)
  {
   *l++ = *r;
  }
  r++;
 }
 *l++ = '\0';
}