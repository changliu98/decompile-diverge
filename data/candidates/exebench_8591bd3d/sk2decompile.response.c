static const char *read_prefix(const char *p, int *has_prefix, int *has_hash,
                               int *has_right_arrow, int *has_left_arrow,
                               int *has_plus, int *has_colon, int *has_bang) {
  *has_prefix = 0;
  *has_right_arrow = 0;
  *has_left_arrow = 0;
  *has_plus = 1;
  *has_hash = 0;
  *has_colon = 0;
  *has_bang = 0;
  for (;; p++) {
    if (*p == '<') {
      *has_prefix = 1;
      *has_left_arrow = 1;
    } else if (*p == '>') {
      *has_prefix = 1;
      *has_right_arrow = 1;
    } else if (*p == '&') {
      *has_prefix = 1;
      *has_left_arrow = 1;
      *has_right_arrow = 1;
    } else if (*p == '+') {
      *has_plus = 0;
    } else if (*p == ':') {
      *has_prefix = 1;
      *has_left_arrow = 1;
      *has_plus = 0;
      *has_bang = 1;
    } else if (*p == '#') {
      *has_hash = 1;
    } else if (*p == '!') {
      *has_colon = 1;
    } else {
      return p;
    }
  }
}