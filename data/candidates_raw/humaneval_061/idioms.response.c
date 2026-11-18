int is_valid_bracket(char *brackets)
{
  int level = 0;
  int i = 0;
  for (i = 0; i < strlen(brackets); i++)
  {
    if (brackets[i] == '(')
      level++;
    if (brackets[i] == ')')
      level--;
    if (level < 0)
      return 0;
  }
  if (level == 0)
    return 1;
  return 0;
}