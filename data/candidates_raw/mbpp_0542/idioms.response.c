char *to_colon(char *text)
{
  int i;
  strcpy(to_colon_result, text);
  for (i = 0; to_colon_result[i]; i++)
    if (to_colon_result[i] == ' ' || to_colon_result[i] == ',' || to_colon_result[i] == '.')
      to_colon_result[i] = ':';
  return to_colon_result;
}