static char *object_desc_chr(char *buf, int c) {
  *buf++ = c;
  *buf = '\0';
  return buf;
}