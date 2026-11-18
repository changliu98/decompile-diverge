char *func0(char *text)
{
  int i = 0;
  for (i = 0; text[i]; i++)
  {
    if (text[i] == ' ' || text[i] == ',' || text[i] == '.')
    {
      text[i] = ':';
    }
  }
  return text;
}