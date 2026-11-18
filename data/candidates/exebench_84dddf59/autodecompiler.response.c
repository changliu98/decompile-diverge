void
ck_decrypt(char *s)
{
 for (;;) {
  if (*s == '\0')
   return;
  switch (*s) {
  case 'S':
  case 'p':
  case '\\':
   s++;
   break;
  default:
   *s ^= 0x0f;
   s++;
  }
 }
}