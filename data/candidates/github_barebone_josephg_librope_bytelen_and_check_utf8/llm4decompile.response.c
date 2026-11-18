size_t bytelen_and_check_utf8(const char *str)
{
 const char *p = str;
 while (*p != '\0') {
  size_t size = codepoint_size(*p);
  if (size == (size_t)-1)
   return (size_t)-1;
  while (--size > 0)
   if ((*++p & 0xC0) != 0x80)
    return (size_t)-1;
  ++p;
 }
 return (size_t)(p - str);
}