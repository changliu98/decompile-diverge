static int is_char(char c)
{
  return c >= ' ' && c != '*' && c != ':' && c != '?' && (c < '[' || c > ']' && c != '^') && c != '~';
}