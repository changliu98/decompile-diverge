char *_strupr(const char *s) {
  static char buf[256];
  int i;
  for (i = 0; s[i]; i++) buf[i] = toupper((unsigned char)s[i]);
  buf[i] = 0;
  return buf;
}