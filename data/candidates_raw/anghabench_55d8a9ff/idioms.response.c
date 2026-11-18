int get_char_val(int c)
{
  if (c >= 'A' && c < 'A'+26)
    return c - 'A';
  if (c >= 'a' && c < 'a'+26)
    return c - 'a';
  if (c >= '1' && c < '1'+10)
    return c - '1';
  if (c >= '!' && c < '!' + 10)
    return c - '!' - 1;
  if (c >= ' ' && c < ' ' + 11)
    return c - ' ' - 1;
  return -1;
}