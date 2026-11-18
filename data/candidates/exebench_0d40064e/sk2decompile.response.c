void prtX16(unsigned long val, char *str) {
  char buf[9];
  int i;
  buf[0] = 0;
  for (i = 1; i < 9; i++) {
    buf[i] = "0123456789ABCDEF"[val & 0x0F];
    val >>= 4;
  }
  for (i = 8; buf[i] == '0'; i--)
    ;
  if (i == 0) i = 1;
  while (i >= 0) *str++ = buf[i--];
}