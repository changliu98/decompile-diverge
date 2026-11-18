int do_map(char *b, int map, char c)
{
 if (c == '\b') {
  if (map & 0x80)
   *b++ = 0x7f;
  else
   *b++ = '\b';
  return 1;
 }
 if (c == '\n') {
  if (map & 0x08) {
   *b++ = '\r';
   return 1;
  }
  if (map & 0x10) {
   *b++ = '\r';
   *b++ = '\n';
   return 2;
  }
  if (map & 0x20)
   return 0;
  *b++ = '\n';
  return 1;
 }
 if (c == '\r') {
  if (map & 0x01) {
   *b++ = '\n';
   return 1;
  }
  if (map & 0x02) {
   *b++ = '\r';
   *b++ = '\n';
   return 2;
  }
  if (map & 0x04)
   return 0;
  *b++ = '\r';
  return 1;
 }
 if (c == 0x7f) {
  if (map & 0x40)
   *b++ = '\b';
  else
   *b++ = 0x7f;
  return 1;
 }
 *b++ = c;
 return 1;
}