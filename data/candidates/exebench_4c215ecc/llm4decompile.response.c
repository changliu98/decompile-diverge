char *
stpcpy0(char *dest, const char *src)
{

 for (; *src != '\0'; src++)
  *dest++ = *src;
 *dest = '\0';
 return (dest);
}