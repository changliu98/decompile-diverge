void process_COM(unsigned char *buf, int len) {
  int i, j, c;
  char s[16000 + 1];
  j = 0;
  if (len > 16000) len = 16000;
  for (i = 2; i < len; i++) {
    c = buf[i];
    if (c != 13 || buf[i + 1] != 10) {
      if (c < 32 && c != 10 && c != 9)
        s[j++] = '?';
      else
        s[j++] = c;
    }
  }
  s[j] = 0;
  if (verbose) printf("COM marker comment: %s\n", s);
  strcpy(header.comment, s);
}