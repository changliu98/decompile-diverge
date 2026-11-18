static char *ikcp_encode8u(char *p, unsigned char v) {
  *p++ = v;
  return p;
}