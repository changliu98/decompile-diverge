void decrypt(char *p, int key) {
  int i;
  for (i = 0; p[i] != '\0'; i++) {
    if (p[i] == '-') {
      p[i] = ' ';
    } else {
      p[i] = ((p[i] - 'a') + (key % 26)) % 26 + 'a';
    }
  }
}