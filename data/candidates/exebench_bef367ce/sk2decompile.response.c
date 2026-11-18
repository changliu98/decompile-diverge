void strcpy4(char *s, char *t) {
  char c;
  do {
    c = *t++;
    *s++ = c;
  } while (c != '\0');
}