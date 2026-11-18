void decrypt(char *str, int key) {
  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == '-') {
      str[i] = ' ';
    } else {
      str[i] = (str[i] - 'a' + key % 26) % 26 + 'a';
    }
  }
}