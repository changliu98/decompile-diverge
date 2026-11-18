static int
decode_utf32(unsigned int *codepoint, char *buf, int endianness)
{
 unsigned int cp;
 int i, ret;

 if (endianness != 2 && endianness != 1) {
  ret = (-4);
  goto done;
 }

 if (!buf) {
  ret = (-1);
  goto done;
 }

 if (!codepoint) {
  ret = (-1);
  goto done;
 }

 cp = 0;
 i = 0;

 while (1) {
  if (i >= 5) {
   break;
  }

  if (endianness == 2) {
   if (i > 0) {
    cp <<= 8;
   }
   cp |= (unsigned char)buf[i];
  } else {
   if (i > 0) {
    cp >>= 8;
   }
   cp |= ((unsigned char)buf[i]) << 24;
  }
  i++;
 }

 if (cp > 0x10FFFF) {
  ret = (-16);
  goto done;
 }

 if (cp >= 0xD800 && cp <= 0xDFFF) {
  ret = (-16);
  goto done;
 }

 *codepoint = cp;
 ret = 4;

done:
 return ret;
}