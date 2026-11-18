static char *unmakemask(int mask, char *buf) {
  int i = 0;
  if (mask & ACL_CHANGE) buf[i++] = 'c';
  if (mask & ACL_READ) buf[i++] = 'r';
  if (mask & ACL_LIST) buf[i++] = 'l';
  buf[i] = '\0';
  return buf;
}