char *tcp_strflags(char *buf, int flags) {
  char *p = buf;
  int i;
  for (i = 0; i < 8; i++) {
    if (flags & (1 << i)) *p++ = "FSRPAYXY"[i];
  }
  *p = '\0';
  return buf;
}