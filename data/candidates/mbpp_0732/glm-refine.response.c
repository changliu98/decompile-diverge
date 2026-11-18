char *__cdecl func0(char *text)
{
  for (int i = 0; text[i]; ++i)
  {
    if (text[i] == ' ' || text[i] == ',' || text[i] == '.')
      text[i] = ':';
  }
  return text;
}