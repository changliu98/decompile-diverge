char *stdimpl_strcpy(char *dest, const char *src)
{
 char *ret = dest;
 char c;

 do {
  c = *src;
  *dest = c;
  src++;
  dest++;
 } while (c != '\0');

 return ret;
}