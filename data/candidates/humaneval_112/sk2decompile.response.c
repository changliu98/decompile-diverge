void func0(char *str, char *chars, char *result, char *isPalindrome) {
  int len = strlen(str);
  char *newStr = malloc(len + 1);
  int newStrIndex = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    char *charsPtr = chars;
    bool found = false;
    while (*charsPtr != '\0') {
      if (str[i] == *charsPtr) {
        found = true;
        break;
      }
      charsPtr++;
    }
    if (!found) {
      newStr[newStrIndex++] = str[i];
    }
  }
  newStr[newStrIndex] = '\0';
  int newStrLen = strlen(newStr);
  bool isPalindromeBool = true;
  for (int i = 0; i < newStrLen / 2; i++) {
    if (newStr[i] != newStr[newStrLen - 1 - i]) {
      isPalindromeBool = false;
      break;
    }
  }
  strcpy(result, newStr);
  strcpy(isPalindrome, isPalindromeBool ? "True" : "False");
  free(newStr);
}