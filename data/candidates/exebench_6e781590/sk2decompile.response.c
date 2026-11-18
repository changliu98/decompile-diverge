void replace_char(char *str, char old, char new) {
  while (*str) {
    if (*str == old) *str = new;
    str++;
  }
}