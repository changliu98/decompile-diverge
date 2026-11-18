char func0(char *str)
{
  int i;
  int len;
  int char_count[-1];
  char char_order[-1];
  int char_order_idx = 0;
  char c;
  str = (char *)str;
  memset(char_count, 0, sizeof(int) * 256);
  for (len = strlen(str), i = 0; i < len; i++)
  {
    c = str[i];
    if (char_count[c] == 0)
    {
      char_order[char_order_idx++] = c;
    }
    char_count[c]++;
  }
  for (i = 0; i < char_order_idx; i++)
  {
    if (char_count[char_order[i]] == 1)
    {
      return char_order[i];
    }
  }
  return '\0';
}