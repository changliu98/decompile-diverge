static int pattern_match_custom_class (int c, char *p, char *ep) {
  int sig = 1;
  if (*p == '^') {
    sig = 0;
    p++;
  }
  while (1) {
    if (++p >= ep) return !sig;
    if (*p == '%') {
      p++;
      if (pattern_match_class(c,*p)) return sig;
      else return !sig;
    }
    else if ((*(p+1) == '-') && (p+2 < ep)) {
      p += 2;
      if (*(p-2) <= c && c <= *p) return sig;
    }
    else if (*p == c) return sig;
  }
}