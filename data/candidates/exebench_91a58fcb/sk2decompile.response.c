void StrBracketMatch(char *str, int *comma, int *comma_last, int *end,
                     int max_comma) {
  int level = 0;
  int i = 0;
  int comma_count = 0;
  char quote = 0;
  while (str[i] != 0) {
    if (quote != 0) {
      if (str[i] == quote && str[i - 1] != '\\') quote = 0;
    } else {
      if (str[i] == '\'' || str[i] == '"')
        quote = str[i];
      else if (str[i] == '(') {
        level++;
        if (level == 1 && comma != NULL &&
            (max_comma < 0 || comma_count < max_comma))
          comma[comma_count++] = i;
      } else if (str[i] == ')') {
        level--;
        if (level == 0) goto end;
      } else if (str[i] == ',' && level == 1 && comma != NULL &&
                 (max_comma < 0 || comma_count < max_comma))
        comma[comma_count++] = i;
    }
    i++;
  }
end:
  if (str[i] == 0) {
    if (comma_last != NULL) *comma_last = -1;
    if (end != NULL) *end = -1;
  } else {
    if (comma != NULL && (max_comma < 0 || comma_count < max_comma))
      comma[comma_count++] = i;
    if (comma_last != NULL) *comma_last = comma_count - 1;
    if (end != NULL) *end = i;
  }
}