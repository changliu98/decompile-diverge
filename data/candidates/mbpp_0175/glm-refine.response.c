// Checks whether the parentheses, brackets, and braces in `str` are balanced.
// Uses an explicit stack (max depth 100). Returns true if every opener is
// matched with a corresponding closer of the same type in the correct order.
bool __cdecl func0(char *str)
{
  char stack[100];      // stack of opening brackets
  int  top   = -1;      // stack pointer (-1 == empty)
  size_t len = strlen(str);

  for (int i = 0; i < len; i++)
  {
    char c = str[i];

    // Push opening brackets onto the stack.
    if (c == '(' || c == '{' || c == '[')
    {
      stack[++top] = c;
    }
    else
    {
      // Closing bracket encountered with nothing to match -> unbalanced.
      if (top == -1)
        return false;

      char popped = stack[top--];

      // Mismatched pair -> unbalanced.
      if ((c == ')' && popped != '(') ||
          (c == '}' && popped != '{') ||
          (c == ']' && popped != '['))
        return false;
    }
  }

  // Balanced only if every opener has been consumed.
  return top == -1;
}