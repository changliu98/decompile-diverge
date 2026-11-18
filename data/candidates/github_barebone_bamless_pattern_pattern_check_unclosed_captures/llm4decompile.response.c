void pattern_check_unclosed_captures(Pattern_State *ps)
{
  int i;

  for (i = 1; i < ps->capture_count; i++)
    if (ps->captures[i].size == -1) {
      int j = 0;
      const char *p = ps->pattern_base;
      const char *pend = p + strlen(p);

      while (p < pend) {
        if (*p == '%') {
          p += 2;
          continue;
        }
        if (*p == '(') {
          j++;
          if (j == i)
            break;
        }
        p++;
      }

      pattern_set_error(ps, PATTERN_ERR_UNCLOSED_CAPTURE, p - ps->pattern_base);
      break;
    }
}