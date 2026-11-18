static char *get_mod_and_div(long *mod, long *div, char *buf, long val) {
  char *ret = buf;
  if (val < 0) {
    *mod = -(val % 10);
    *div = val / -10;
    *buf = '-';
    buf++;
  } else {
    *mod = val % 10;
    *div = val / 10;
  }
  return ret;
}