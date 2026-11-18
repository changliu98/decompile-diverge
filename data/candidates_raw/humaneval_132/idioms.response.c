int is_valid_json(char *str)
{
  int count = 0;
  int maxcount = 0;
  int i;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '[')
      count++;
    if (str[i] == ']')
      count--;
    if (count < 0)
      count = 0;
    if (count > maxcount)
      maxcount = count;
    if (count <= maxcount - 2)
      return 1;
  }
  return 0;
}