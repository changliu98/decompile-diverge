void cgi_sys_get_action(char *buf) {
  int *p = (int *)buf;
  p[1] = 6;
  p[2] = 1;
}