int
runetochar(char *s, Rune r)
{

 if(r < 0x80) {
  s[0] = r;
  return 1;
 }


 if(r < 0x800) {
  s[0] = 0xC0 | (r >> 6);
  s[1] = 0x80 | (r & 0x3F);
  return 2;
 }


 if(r < 0x10000) {
  s[0] = 0xE0 | (r >> 12);
  s[1] = 0x80 | ((r >> 6) & 0x3F);
  s[2] = 0x80 | (r & 0x3F);
  return 3;
 }


 if(r < 0x110000) {
  s[0] = 0xF0 | (r >> 18);
  s[1] = 0x80 | ((r >> 12) & 0x3F);
  s[2] = 0x80 | ((r >> 6) & 0x3F);
  s[3] = 0x80 | (r & 0x3F);
  return 4;
 }


 s[0] = 0xEF;
 s[1] = 0xBF;
 s[2] = 0xBD;
 return 3;
}