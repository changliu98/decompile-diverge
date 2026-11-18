size_t bytelen_and_check_utf8(char *s)
{
 size_t len;
 size_t i;
 unsigned char *c;

 for (c = (unsigned char *) s, len = 0; *c != '\0'; ++len) {
  i = codepoint_size(*c);
  if (i == (size_t) -1)
   return (size_t) -1;

  ++c;

  while (i > 1) {
   if ((*c & 0xc0) != 0x80)
    return (size_t) -1;

   ++c;
   --i;
  }
 }

 return c - (unsigned char *) s;
}