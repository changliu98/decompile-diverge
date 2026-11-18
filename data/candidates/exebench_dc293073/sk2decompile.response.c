char *Q_strupr(char *s) {
  char *p;
  for (p = s; *p; p++) {
    if (*p >= 'a' && *p <= 'z') {
      *p -= 'a' - 'A';
    }
  }
  return s;
}