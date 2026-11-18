void word2string(unsigned int word, char *string) {
  char *p = string;
  int i;
  static unsigned int div[] = {10000, 1000, 100, 10, 1};
  if (word == 0) {
    string[0] = '0';
    string[1] = ' ';
    return;
  }
  for (i = 0; i < 5; i++) {
    if (p + word / div[i] != string) {
      *p = word / div[i] + '0';
      p++;
      word %= div[i];
    }
  }
  p[0] = ' ';
  p[1] = '\0';
}