static int is_valid_ref_char(char c)
{
  return c >= ' ' && c != '*' && c != ':' && c != '?' && (c < '[' || c > ']' && c != '^') && c != '~';
}