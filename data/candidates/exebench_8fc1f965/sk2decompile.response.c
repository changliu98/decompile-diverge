void murcielagoCrypt(char *text) {
  int i, j;
  for (i = 0; text[i] != '\0'; i++) {
    for (j = 0; alphabet[j] != '\0'; j++) {
      if (text[i] == alphabet[j]) {
        text[i] = murcielago[j];
        break;
      }
    }
  }
}