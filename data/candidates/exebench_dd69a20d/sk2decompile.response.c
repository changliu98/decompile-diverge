void remove_all_chars(char *str, char bad) {
  char *read = str;
  char *write = str;
  while (*read) {
    *write = *read++;
    if (*write != bad) write++;
  }
  *write = '\0';
}