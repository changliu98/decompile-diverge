char* func0(const char* text) {
  static char buffer[100];
  int i = 0, j = 0;
  while (text[i] != '\0') {
    if (isupper(text[i])) {
      if (i != 0 && (islower(text[i - 1]) || isdigit(text[i - 1]))) {
        buffer[j++] = '_';
      }
      buffer[j++] = tolower(text[i]);
    } else {
      buffer[j++] = text[i];
    }
    i++;
  }
  buffer[j] = '\0';
  return buffer;
}