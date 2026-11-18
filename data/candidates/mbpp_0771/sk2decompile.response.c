bool _isValid(char *s) {
  char *str = s;
  int len = strlen(s);
  if (len % 2 != 0) {
    return false;
  }
  char stack[100];
  int top = -1;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == '(' || c == '{' || c == '[') {
      top++;
      stack[top] = c;
    } else if (c == ')' || c == '}' || c == ']') {
      if (top == -1) {
        return false;
      }
      char topChar = stack[top--];
      if (topChar == '(' && c != ')') {
        return false;
      }
      if (topChar == '{' && c != '}') {
        return false;
      }
      if (topChar == '[' && c != ']') {
        return false;
      }
    }
  }
  return top == -1;
}