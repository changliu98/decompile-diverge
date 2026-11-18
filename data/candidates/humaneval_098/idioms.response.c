int func0(char *str)
{
  int count = 0;
  int i = 0;
  while (1)
  {
    int is_char = 0;
    if (str[i])
      is_char = i * 2 < strlen(str);
    if (!is_char)
      break;
    if (strchr("AEIOU", str[i * 2]))
      count++;
  }
  return count;
}