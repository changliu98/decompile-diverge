static void
encode_int(char *buf, int val)
{
 int negative = 0;

 if (val > 0) {
  if ((val & 0x7c00) != 0)
   *buf++ = 0x40 | ((val >> 10) & 0x1f);
  if ((val & 0x3f0) != 0)
   *buf++ = 0x40 | ((val >> 4) & 0x3f);
 } else {
  val = -val;
  negative = 1;
 }
 if ((val & 0xf) != 0)
  *buf = 0x20 | (val & 0xf);
 else
  *buf = ' ';
 if (!negative)
  *buf |= 0x10;
 buf++;
 *buf = '\0';
}