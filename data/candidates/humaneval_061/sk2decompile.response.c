bool _isValid(char* s) {
  int count = 0;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '(') count++;
    if (s[i] == ')') count--;
    if (count < 0) return false;
  }
  return count == 0;
}