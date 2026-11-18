int func0(char *str)
{
  int len = strlen(str);
  if (len % 2 != 0)
    return 0;
  char stack[100];
  int top = -1;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == '(' || c == '{' || c == '[')
      stack[++top] = c;
    else if (c == ')' || c == '}' || c == ']') {
      if (top == -1)
        return 0;
      char last_open = stack[top--];
      if (last_open == '(' && c != ')')
        return 0;
      if ((last_open == '{' && c != '}') || (last_open == '[' && c != ']'))
        return 0;
    }
  }
  if (top != -1)
    return 0;
  return 1;
}