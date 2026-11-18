int char2num(char c, unsigned char *num) {
  int ret = 0;
  if (c >= '0' && c <= '9') {
    *num = c - '0';
  } else if (c >= 'A' && c <= 'F') {
    *num = c - 'A' + 10;
  } else if (c >= 'a' && c <= 'f') {
    *num = c - 'a' + 10;
  } else {
    ret = -1;
  }
  return ret;
}