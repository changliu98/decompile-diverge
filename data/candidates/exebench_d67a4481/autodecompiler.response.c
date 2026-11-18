int Utf8ToUnicode(char *s, unsigned long *code, int *len, size_t left)
{
 char c;
 int ret;

 c = *s;
 if ((c & 0xf8) == 0xf0) {
  if (left < 4 || (s[1] & 0xc0) != 0x80 ||
      (s[2] & 0xc0) != 0x80 || (s[3] & 0xc0) != 0x80) {
   ret = 2;
   goto err;
  }
  *len = 4;
  *code |= c & 0x07;
  *code <<= 6;
  c = s[1];
  *code |= c & 0x3f;
  *code <<= 6;
  c = s[2];
  *code |= c & 0x3f;
  *code <<= 6;
  c = s[3];
  *code |= c & 0x3f;
 } else if ((c & 0xf0) == 0xe0) {
  if (left < 3 || (s[1] & 0xc0) != 0x80 ||
      (s[2] & 0xc0) != 0x80) {
   ret = 2;
   goto err;
  }
  *len = 3;
  *code |= c & 0x0f;
  *code <<= 6;
  c = s[1];
  *code |= c & 0x3f;
  *code <<= 6;
  c = s[2];
  *code |= c & 0x3f;
 } else if ((c & 0xe0) == 0xc0) {
  if (left < 2 || (s[1] & 0xc0) != 0x80) {
   ret = 2;
   goto err;
  }
  *len = 2;
  *code |= c & 0x1f;
  *code <<= 6;
  c = s[1];
  *code |= c & 0x3f;
 } else if ((c & 0x80) == 0) {
  *len = 1;
  *code = c;
 } else {
  ret = 1;
  goto err;
 }

 ret = 0;
err:
 return ret;
}