static void pattern_check_unclosed_captures(Pattern *pat) {
  int i;
  for (i = 1; i < pat->num_captures; i++) {
    if (pat->captures[i].end == -1) {
      int num_open = 0;
      const char *p = pat->pattern;
      while (p < pat->pattern + strlen(pat->pattern)) {
        if (*p == '%') {
          p += 2;
        } else if (*p == '(') {
          num_open++;
          if (num_open == i) {
            break;
          }
          p++;
        } else {
          p++;
        }
      }
      pattern_set_error(pat, PATTERN_ERROR_UNCLOSED_CAPTURE, p - pat->pattern);
      return;
    }
  }
}