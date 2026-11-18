char* func0(const char* string) {
  static char result[100];
  int i;
  for (i = 0; string[i] != '\0'; i++) {
    result[i] = toupper((unsigned char)string[i]);
  }
  result[i] = '\0';
  return result;
}