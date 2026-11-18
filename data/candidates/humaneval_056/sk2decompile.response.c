bool _is_balanced(char *str) {
  int count = 0;
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == '<') count++;
    if (str[i] == '>') count--;
    if (count < 0) return false;
  }
  return count == 0;
}