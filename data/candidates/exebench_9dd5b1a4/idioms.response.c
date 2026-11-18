int add_char_to_string(char *str, char c, int size)
{
  int i;
  if (!str)
    return 0;
  for (i = 0; str[i]; i++)
    ;
  if (i >= size - 1)
    return 0;
  str[i] = c;
  str[i + 1] = '\0';
  return 1;
}