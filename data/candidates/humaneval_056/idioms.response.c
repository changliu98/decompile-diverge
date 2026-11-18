int func0(char *text)
{
  int level = 0;
  int i = 0;
  for (i = 0; text[i]; i++) {
    if (text[i] == '<')
      level++;
    if (text[i] == '>')
      level--;
    if (level < 0)
      return 0;
  }
  if (level == 0)
    return 1;
  return 0;
}