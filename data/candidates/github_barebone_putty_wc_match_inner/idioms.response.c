int wc_match_inner(char *wildcard, char *target, unsigned long target_len)
{
  char *wildcarda = wildcard;
  char *targeta = target;
  char *target_end = target + target_len;
  int ret;
  if (*wildcard != '*') {
    ret = match_one(&wildcarda, &targeta, target_end);
    if (ret <= 0)
      return ret;
  }
  for (; *wildcard; ++wildcard) {
    ((void) sizeof ((*wildcard == '*') ? 1 : 0), __extension__ ({ if (*wildcard == '*') ; else __assert_fail ("*wildcard == '*'", "func.c", 228, __extension__ __PRETTY_FUNCTION__); }));
    while (*wildcard == '*')
      ++wildcard;
    if (!*wildcard)
      return 1;
    ret = 0;
    for (; *targeta; ++targeta) {
      char *save_w = wildcard;
      char *save_t = targeta;
      ret = match_one(&wildcarda, &targeta, target_end);
      if (ret < 0)
        return ret;
      if (ret > 0 && !*wildcard && targeta != target_end) {
        targeta = target_end + (save_t - targeta);
        wildcard = save_w;
        ret = match_one(&wildcarda, &targeta, target_end);
        return ret;
      }
      if (ret > 0)
        break;
    }
    if (ret <= 0)
      return ret;
  }
  return targeta == target_end;
}