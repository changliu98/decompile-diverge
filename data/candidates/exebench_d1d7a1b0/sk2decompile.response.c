char *unmakemask(int mask, char *buf) {
  int i = 0;
  if (mask & 1) buf[i++] = 'c';
  if (mask & 2) buf[i++] = 'r';
  if (mask & 4) buf[i++] = 'l';
  buf[i] = '\0';
  return buf;
}