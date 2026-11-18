static int render_uint32(unsigned int val, char *bf) {
  static const char *h[] = {"", "k", "M", "G", "T", "P", "E", "Z", "Y"};
  int i;
  if (val == 0) {
    bf[0] = '0';
    return 1;
  }
  i = 0;
  while (val > 0 && i < sizeof(h) / sizeof(h[0])) {
    bf[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[val & 0x0f];
    val >>= 4;
  }
  return i;
}