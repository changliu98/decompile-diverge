static int is_valid_ref_char(char c) {
  return c > 32 && c != '*' && c != ':' && c != '?' && c != '[' && c != ']' &&
         c != '^' && c != '~';
}