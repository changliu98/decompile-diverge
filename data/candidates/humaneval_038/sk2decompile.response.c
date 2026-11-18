void _base64_encode(char *str, int reverse) {
  int len = strlen(str);
  int n = (len + 2) / 3;
  int i;
  char buf[4];
  char tmp;
  int l;
  for (i = 0; i < n; i++) {
    l = (i + 1) * 3 > len ? len - i * 3 : 3;
    strncpy(buf, str + i * 3, l);
    buf[l] = '\0';
    if (l == 3) {
      if (reverse) {
        tmp = buf[2];
        buf[2] = buf[1];
        buf[1] = buf[0];
        buf[0] = tmp;
      } else {
        tmp = buf[0];
        buf[0] = buf[1];
        buf[1] = buf[2];
        buf[2] = tmp;
      }
    }
    strncpy(str + i * 3, buf, l);
  }
}