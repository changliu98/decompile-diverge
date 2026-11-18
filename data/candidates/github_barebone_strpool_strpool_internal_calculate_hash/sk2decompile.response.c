static unsigned int strpool_internal_calculate_hash(const char *str, int len,
                                                    int case_insensitive) {
  unsigned int hash = 5381;
  int i;
  if (case_insensitive) {
    for (i = 0; i < len; i++) {
      char c = str[i];
      if (c <= 'z' && c >= 'a') {
        c -= 32;
      }
      hash = ((hash << 5) + hash) ^ c;
    }
  } else {
    for (i = 0; i < len; i++) {
      hash = ((hash << 5) + hash) ^ str[i];
    }
  }
  if (hash == 0) {
    hash = 1;
  }
  return hash;
}