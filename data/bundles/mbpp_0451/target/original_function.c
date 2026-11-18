char* func0(char* text1) {
  int i = 0, j = 0;
  while (text1[i]) {
    if (!isspace((unsigned char)text1[i])) {
      text1[j++] = text1[i];
    }
    i++;
  }
  text1[j] = '\0';
  return text1;
}