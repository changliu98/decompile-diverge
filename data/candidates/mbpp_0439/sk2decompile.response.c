int func0(int *p, int n) {
  int *a = p;
  int len = n;
  char buf[256];
  char tmp[20];
  int i;
  memset(buf, 0, 256);
  for (i = 0; i < len; i++) {
    sprintf(tmp, "%d", a[i]);
    strcat(buf, tmp);
  }
  return atoi(buf);
}