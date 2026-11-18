void cenitPolarCrypt(char *str) {
  int i, j;
  for (i = 0; str[i] != '\0'; i++) {
    for (j = 0; cenitPolarAlphabet[j] != '\0'; j++) {
      if (str[i] == cenitPolarAlphabet[j]) {
        str[i] = cenitPolarCryptAlphabet[j];
        break;
      }
    }
  }
}