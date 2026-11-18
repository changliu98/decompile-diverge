static void stress_chop(char *str, const char c) {
  char *p;
  p = strchr(str, c);
  if (p) *p = '\0';
}