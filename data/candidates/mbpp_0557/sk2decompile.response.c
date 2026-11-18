char *func0(char *str) {
  int i;
  strcpy(str1, str);
  for (i = 0; str1[i] != '\0'; i++) {
    if (isupper(str1[i]))
      str1[i] = tolower(str1[i]);
    else if (islower(str1[i]))
      str1[i] = toupper(str1[i]);
  }
  return str1;
}