void util_word_to_dec(char *str, unsigned int val) {
  char buf[11];
  int i, j;
  for (i = 0; i < 10; i++) buf[i] = '0';
  buf[10] = '\0';
  i = 10 - 1;
  while (val > 0) {
    int digit = val % 10;
    val /= 10;
    buf[i--] = '0' + digit;
  }
  i = 0;
  while (buf[i] == '0' && i < 10 - 1) i++;
  while (buf[i] != '\0') *str++ = buf[i++];
  *str = '\0';
}