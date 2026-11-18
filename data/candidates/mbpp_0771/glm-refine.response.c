bool __cdecl func0(const char *exp)
{
  char stack[100];
  int top = -1;
  int len = strlen(exp);

  // A valid bracket sequence must have an even length
  if (len % 2 != 0)
    return false;

  for (int i = 0; i < len; ++i)
  {
    char ch = exp[i];

    // If it's an opening bracket, push it onto the stack
    if (ch == '(' || ch == '{' || ch == '[')
    {
      stack[++top] = ch;
    }
    // If it's a closing bracket, check for matching opening bracket
    else if (ch == ')' || ch == '}' || ch == ']')
    {
      // If stack is empty, there's no matching opening bracket
      if (top == -1)
        return false;

      char last_open = stack[top--];

      // Check for bracket mismatch
      if ((last_open == '(' && ch != ')') ||
          (last_open == '{' && ch != '}') ||
          (last_open == '[' && ch != ']'))
      {
        return false;
      }
    }
  }

  // If the stack is empty, all brackets were successfully matched
  return top == -1;
}