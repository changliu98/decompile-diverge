void break_at(char *s, char c) {
  char *p;
  p = strchr(s, c);
  if (p) *p = '\0';
}