int add_char_to_string(char *str, char c, int max_len) {
  int i;
  if (str == NULL) return 0;
  for (i = 0; str[i] != '\0'; i++)
    ;
  if (i >= max_len - 1) return 0;
  str[i] = c;
  str[i + 1] = '\0';
  return 1;
}