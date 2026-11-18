char *func0(char *original, char *blessed) {
  int *cc = get_char_count_array(blessed);
  int ri, oi;
  char *o = str_to_list(original);

  for(oi = 0, ri = 0; ; oi++, ri++) {
    if (o[oi] == '\0') break;
    char c = o[oi];
    if (!cc[c]) {
      o[ri++] = c;
    }
  }

  return lst_to_string(o, ri);
}