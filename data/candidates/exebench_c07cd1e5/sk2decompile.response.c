void replaceChar(char *str, char oldChar, char newChar) {
  if (str == NULL) return;
  while (*str != '\0') {
    if (*str == oldChar) *str = newChar;
    str++;
  }
}