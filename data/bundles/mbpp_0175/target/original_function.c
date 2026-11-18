bool func0(char* str1) {
  char stack[100];
  int top = -1;
  for (int i = 0; i < strlen(str1); i++) {
    char parenthese = str1[i];
    if (parenthese == '(' || parenthese == '{' || parenthese == '[') {
      stack[++top] = parenthese;
    } else if (top == -1) {
      return false;
    } else {
      char popped = stack[top--];
      if ((parenthese == ')' && popped != '(') ||
          (parenthese == '}' && popped != '{') ||
          (parenthese == ']' && popped != '[')) {
        return false;
      }
    }
  }
  return top == -1;
}