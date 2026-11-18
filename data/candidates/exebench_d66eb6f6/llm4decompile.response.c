int bcd2int(unsigned char *b, int len)
{
 int i, out;

 if (len > 5)
  return 0;

 out = 0;
 for (i = 0; i < len; i++) {
  out *= 100;
  out += (b[i] / 16) * 10;
  out += b[i] % 16;
 }

 return out;
}