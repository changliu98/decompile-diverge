char* func0(const char* text) {
  size_t length = strlen(text);
  size_t new_length = 0;
  char* result = (char*)malloc(sizeof(char) * (length * 2));
  int i, j = 0;
  for (i = 0; i < length; i++) {
    if (i > 0 && isupper(text[i]) &&
        (islower(text[i - 1]) || isdigit(text[i - 1]))) {
      result[j++] = '_';
      result[j++] = tolower(text[i]);
    } else if (i > 0 && isupper(text[i]) && isupper(text[i - 1]) &&
               islower(text[i + 1])) {
      result[j++] = '_';
      result[j++] = tolower(text[i]);
    } else {
      result[j++] = tolower(text[i]);
    }
  }
  result[j] = '\0';
  return result;
}