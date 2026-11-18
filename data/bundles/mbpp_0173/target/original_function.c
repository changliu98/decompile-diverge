char* func0(char* text) {
  int i = 0, j = 0;
  char temp[strlen(text) + 1];
  while (text[i]) {
    if (isalnum(text[i])) {
      temp[j++] = text[i];
    }
    i++;
  }
  temp[j] = '\0';
  strcpy(text, temp);
  return text;
}