static char_u *regtilde(char_u *pat, int is_search) {
  char_u *newpat;
  char_u *newpat_p;
  char_u *p;
  int len;
  int pos;
  newpat = newpat_p = pat;
  for (p = pat; *p != '\0'; p++) {
    if ((*p == '~' && is_search) ||
        (*p == '\\' && p[1] == '~' && !is_search)) {
      if (regtilde_tilde != NULL) {
        len = strlen(regtilde_tilde);
        newpat_p = alloc(strlen(newpat) + len);
        if (newpat_p != NULL) {
          pos = p - newpat;
          memmove(newpat_p, newpat, pos);
          memmove(newpat_p + pos, regtilde_tilde, len);
          if (!is_search) p++;
          strcpy(newpat_p + pos + len, p + 1);
          if (newpat != pat) {
            (void)QScopedPointerPodDeleter::cleanup(newpat);
          }
          newpat = newpat_p;
          p = newpat_p + pos + len;
        }
      } else {
        if (is_search)
          memmove(p, p + 1, strlen(p + 1) + 1);
        else
          memmove(p, p + 2, strlen(p + 2) + 1);
      }
      p--;
    } else {
      if (*p == '\\' && p[1] != '\0') p++;
      if (mb_mode) p += mb_ptr2len(p) - 1;
    }
  }
  (void)QScopedPointerPodDeleter::cleanup(regtilde_tilde);
  regtilde_tilde = vim_strsave(newpat);
  return newpat;
}