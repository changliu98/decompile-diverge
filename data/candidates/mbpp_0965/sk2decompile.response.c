char *_to_lower_case(const char *str) {
  int i = 0, j = 0;
  while (str[i]) {
    if (!isalnum(str[i])) {
      _lower_case[j++] = str[i];
    } else {
      if (i && (isupper(str[i - 1]) || isdigit(str[i - 1]))) {
        _lower_case[j++] = '_';
      }
      _lower_case[j++] = tolower(str[i]);
    }
    i++;
  }
  _lower_case[j] = '\0';
  return _lower_case;
}