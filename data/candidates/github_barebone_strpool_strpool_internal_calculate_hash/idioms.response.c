int strpool_internal_calculate_hash(char *str, int len, int ignore_case)
{
  int hash = 5381;
  int i;
  if (ignore_case) {
    for (i = 0; i < len; i++) {
      char c = str[i];
      char c2 = (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
      hash = ((hash << 5) + hash) ^ c2;
    }
  } else {
    for (i = 0; i < len; i++) {
      hash = ((hash << 5) + hash) ^ str[i];
    }
  }
  if (hash == 0) {
    return 1;
  } else {
    return hash;
  }
}