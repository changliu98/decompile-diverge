void ToIUPAC(char *seq, int is_aseq) {
  char *p;
  char *validchars = "ACGTUNRYMKSWHBVDacgtunrymkswhbvd";

  p = seq;
  if (is_aseq) {
    while (*p != '\0') {
      if (strchr(validchars, *p) == NULL &&
          *p != ' ' && *p != '.' &&
          *p != '_' && *p != '-' &&
          *p != '~') {
        *p = 'N';
      }
      p++;
    }
  }
  else {
    while (*p != '\0') {
      if (strchr(validchars, *p) == NULL) {
        *p = 'N';
      }
      p++;
    }
  }
}