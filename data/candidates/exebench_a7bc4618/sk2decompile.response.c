void remove_line_ending(char *str, char c) {
  char *p;
  p = strrchr(str, c);
  if (p) {
    *p = '\0';
  }
}