static int pattern_match_custom_class(char c, const char *p, const char *end) {
  int match = 1;
  if (*(p + 1) == '^') {
    match = 0;
    p++;
  }
  p++;
  while (p < end) {
    if (*p == '%') {
      p++;
      if (pattern_match_class(c, *p)) return match;
    } else if (*(p + 1) == '-' && p + 2 < end) {
      p += 2;
      if (c >= *(p - 2) && c <= *p) return match;
    } else if (*p == c)
      return match;
    p++;
  }
  return !match;
}