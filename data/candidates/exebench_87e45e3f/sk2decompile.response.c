void encode_int(char *buf, int val) {
  int sign = 0;
  if (val <= 0) {
    val = -val;
    sign = 1;
  }
  if (val & 0x7c00) *buf++ = ((val >> 10) & 0x1f) | 0x40;
  if (val & 0x03f0) *buf++ = ((val >> 4) & 0x3f) | 0x40;
  if (val & 0x000f)
    *buf++ = (val & 0x0f) | 0x20;
  else
    *buf++ = ' ';
  if (!sign) *buf++ |= 0x10;
  *buf = 0;
}