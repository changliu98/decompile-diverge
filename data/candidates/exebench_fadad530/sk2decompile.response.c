void ToIUPAC(char *seq, int is_dna) {
  if (is_dna) {
    for (; *seq; seq++) {
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == NULL &&
          *seq != ' ' && *seq != '.' && *seq != '_' && *seq != '-' &&
          *seq != '~')
        *seq = 'N';
    }
  } else {
    for (; *seq; seq++) {
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == NULL) *seq = 'N';
    }
  }
}