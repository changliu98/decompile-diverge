int bcd2int(unsigned char *bcd, int len) {
  int i, val;
  if (len > 5) return 0;
  val = 0;
  for (i = 0; i < len; i++) {
    val *= 100;
    val += (bcd[i] / 16) * 10;
    val += bcd[i] % 16;
  }
  return val;
}