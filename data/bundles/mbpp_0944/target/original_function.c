int func0(const char *text) {
  for (int i = 0; text[i] != '\0'; i++) {
    if (isdigit(text[i])) {
      return i;
    }
  }
  return -1;
}