char *vips_utf8_strcasestr(char *str, char *find, int len)
{
  int needle_len = mbstrlen(find, -1);
  int needle_len_bytes = mbstrlenbytes(find);
  char *str_char; char *find_char;
  int i;
  for (str = str; str - str < len - needle_len_bytes; str = mbnext(str, ((void *)0)))
  {
    str_char = str;
    find_char = find;
    for (i = 0; i < needle_len; i++)
    {
      int str_ch = mbtoext(str_char, str + len - str);
      int find_ch = mbtoext(find_char, -1);
      if (str_ch == -1 || str_ch == -2 || find_ch == -2)
        return ((void *)0);
      if (str_ch == 0)
        return ((void *)0);
      int str_ch_lower = mbtolower(str_ch);
      int find_ch_lower = mbtolower(find_ch);
      if (str_ch_lower != find_ch_lower)
        break;
      str_char = mbnext(str_char, str + len);
      find_char = mbnext(find_char, ((void *)0));
    }
    if (i == needle_len)
      return (char *)str;
  }
  return ((void *)0);
}