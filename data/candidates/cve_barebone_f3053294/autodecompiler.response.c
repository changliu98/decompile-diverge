char *utf_16le_to_utf_8_truncated(unsigned int *in, char *out, size_t outlen)
{
 unsigned int c, d;
 char *s;

 if (outlen == 0)
 {
  s = out;
  goto done;
 }

 while ((c = *in++))
 {
  if (c >= 0xD800 && c < 0xDC00)
  {

   d = *in++;
   if (d == 0)
   {
    c = 0xFFFD;
   }
   else
   {
    c = (((c) - 0xD800) << 10 | ((d) - 0xDC00)) + 0x10000;
   }
  }
  else if (c >= 0xDC00 && c < 0xE000)
  {
   c = 0xFFFD;
  }

  if (c < 0x80)
  {
   if (outlen < 3) break;
   *out++ = c;
   outlen--;
  }
  else if (c < 0x800)
  {
   if (outlen < 4) break;
   *out++ = 0xC0 | (c >> 6);
   *out++ = 0x80 | (c & 0x3F);
   outlen -= 2;
  }
  else if (c < 0x10000)
  {
   if (outlen < 5) break;
   *out++ = 0xE0 | (c >> 12);
   *out++ = 0x80 | ((c >> 6) & 0x3F);
   *out++ = 0x80 | (c & 0x3F);
   outlen -= 3;
  }
  else
  {
   if (outlen < 6) break;
   *out++ = 0xF0 | (c >> 18 & 0x3);
   *out++ = 0x80 | ((c >> 12) & 0x3F);
   *out++ = 0x80 | ((c >> 6) & 0x3F);
   *out++ = 0x80 | (c & 0x3F);
   outlen -= 3;
  }
 }
 *out = '\0';
 s = out;

done:
 return s;
}