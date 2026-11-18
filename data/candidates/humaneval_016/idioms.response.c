int func0(char *str)
{
  int i;
  int count = 0;
  int char_map[-1];
  char c;
  memset(char_map, 0, sizeof(char_map));
  for (i = 0; str[i]; i++)
  {
    c = tolower((unsigned char)str[i]);
    if (char_map[c] == 0 && ((*__ctype_b_loc ())[(int) ((unsigned char) c)] & (unsigned short) _ISalpha))
    {
      char_map[c] = 1;
      count++;
    }
  }
  return (count);
}