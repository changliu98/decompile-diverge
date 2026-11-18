int func0(char* str) {
  int count = 0;
  int i;
  for (i = 0; str[i] != '\0' && i * 2 < strlen(str); i++) {
    if (strchr("AEIOU", str[i * 2]) != NULL) {
      count++;
    }
  }
  return count;
}