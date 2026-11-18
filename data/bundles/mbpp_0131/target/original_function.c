char* func0(char* str1) {
  static char result_string[100];
  int i, j = 0;
  char vowels[100] = "";
  for (i = 0; str1[i] != '\0'; i++) {
    char char1 = str1[i];
    if (strchr("aeiouAEIOU", char1) != NULL) {
      vowels[j++] = char1;
    }
  }
  vowels[j] = '\0';
  j = 0;
  int k = strlen(vowels) - 1;
  for (i = 0; str1[i] != '\0'; i++) {
    char char1 = str1[i];
    if (strchr("aeiouAEIOU", char1) != NULL) {
      result_string[j++] = vowels[k--];
    } else {
      result_string[j++] = str1[i];
    }
  }
  result_string[j] = '\0';
  return result_string;
}