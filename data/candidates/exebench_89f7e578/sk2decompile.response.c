void put_num(unsigned short *p, unsigned int n, unsigned char digits) {
  if (digits >= 5) *p++ = (16 + (n / 10000) % 10) | 0x2100;
  if (digits >= 4) *p++ = (16 + (n / 1000) % 10) | 0x2100;
  if (digits >= 3) *p++ = (16 + (n / 100) % 10) | 0x2100;
  if (digits >= 2) *p++ = (16 + (n / 10) % 10) | 0x2100;
  if (digits >= 1) *p++ = (16 + (n % 10)) | 0x2100;
}