void misc_str_remove_symbol(char *str, char symbol) {
  int j = 0;
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] != symbol) {
      str[j] = str[i];
      j++;
    }
  }
  str[j] = '\0';
}