char* func0(const char* str1) {
  size_t len = strlen(str1);
  char* result = malloc(len + 1);
  if (!result) return NULL;
  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if (!isupper((unsigned char)str1[i])) {
      result[j++] = str1[i];
    }
  }
  result[j] = '\0';
  return result;
}