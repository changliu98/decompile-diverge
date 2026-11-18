size_t utf8_to_unicode(char *str, size_t len, unsigned long *code)
{
 size_t ret;
 unsigned char c;

 if (len > 0) {
  c = str[0];
  if ((c & 0x80) == 0) {
   *code = c;
   ret = 1;
  } else if ((c & 0xe0) == 0xc0) {
   if (len >= 2) {
    *code = ((unsigned long)(c & 0x1f)) << 6 | ((unsigned long)(str[1] & 0x3f));
    ret = 2;
   } else {
    goto error;
   }
  } else if ((c & 0xf0) == 0xe0) {
   if (len >= 3) {
    *code = ((unsigned long)(c & 0x0f)) << 12 | ((unsigned long)(str[1] & 0x3f)) << 6 | ((unsigned long)(str[2] & 0x3f));
    ret = 3;
   } else {
    goto error;
   }
  } else if ((c & 0xf8) == 0xf0) {
   if (len >= 4) {
    *code = ((unsigned long)(c & 0x07)) << 18 | ((unsigned long)(str[1] & 0x3f)) << 12 | ((unsigned long)(str[2] & 0x3f)) << 6 | ((unsigned long)(str[3] & 0x3f));
    ret = 4;
   } else {
    goto error;
   }
  } else {
error:
   *code = 0;
   ret = 0;
  }
 } else {
  ret = 0;
 }

 return ret;
}