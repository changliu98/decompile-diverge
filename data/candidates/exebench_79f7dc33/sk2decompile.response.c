void bToHex0(char *s, unsigned char b) {
  s[0] = "0123456789ABCDEF"[(b >> 4) & 0x0F];
  s[1] = "0123456789ABCDEF"[b & 0x0F];
  s[2] = '\0';
}