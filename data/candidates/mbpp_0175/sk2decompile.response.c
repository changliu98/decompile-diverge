bool _isValid(char *s) {
  char *str = s;
  char stack[100];
  int top = -1;
  for (int i = 0; i < strlen(str); i++) {
    char c = str[i];
    if (c == '(' || c == '{' || c == '[') {
      top++;
      stack[top] = c;
    } else {
      if (top == -1) {
        return false;
      }
      char t = stack[top--];
      if ((c == ')' && t != '(') || (c == '}' && t != '{') ||
          (c == ']' && t != '[')) {
        return false;
      }
    }
  }
  return top == -1;
}