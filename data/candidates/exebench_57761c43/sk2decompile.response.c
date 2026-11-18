void char_replace(char *str, char old, char new) {
  while (*str++) {
    if (*str == old) {
      *str = new;
    }
  }
}