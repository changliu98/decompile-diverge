void cgi_store_get_action(char *buf) {
  int *p = (int *)buf;
  p[1] = 4;
  p[2] = 1;
}