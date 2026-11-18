char *isis_print_id(unsigned char *id, int len) {
  static char id_str[21];
  char *p = id_str;
  int i;
  for (i = 1; i <= 6; i++) {
    snprintf(p, 21 - (p - id_str), "%02x", *id++);
    p += strlen(p);
    if (i == 2 || i == 4) *p++ = '.';
  }
  if (len >= 7) {
    snprintf(p, 21 - (p - id_str), ".%02x", *id++);
    p += strlen(p);
  }
  if (len == 8) snprintf(p, 21 - (p - id_str), "-%02x", *id);
  return id_str;
}