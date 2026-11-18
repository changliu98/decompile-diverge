void cgi_alert_get_action(char *buf) {
  int *p = (int *)buf;
  p[1] = 3;
  p[2] = 1;
}