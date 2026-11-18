char *func0(char *str) {
  int i = 0, j = 0;
  char temp[strlen(str) + 1];
  while (str[i] != '\0') {
    if (isalnum(str[i])) {
      temp[j++] = str[i];
    }
    i++;
  }
  temp[j] = '\0';
  strcpy(str, temp);
  return str;
}