char *js_itoa(char *buf, unsigned int value) {
  char tmp[32];
  char *ret = buf;
  unsigned int val = value;
  char *p = buf;
  unsigned int i = 0;
  while (val) {
    tmp[i++] = '0' + (val % 10);
    val /= 10;
  }
  if (i == 0) {
    i = 1;
    tmp[0] = '0';
  }
  while (i) {
    i--;
    *p++ = tmp[i];
  }
  *p = '\0';
  return ret;
}