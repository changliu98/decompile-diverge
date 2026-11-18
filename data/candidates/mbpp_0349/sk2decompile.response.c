char *_01_string(char *s) {
  int i;
  int has_0 = 0;
  int has_1 = 0;
  int has_other = 0;
  for (i = 0; i < strlen(s); i++) {
    if (s[i] == '0') {
      has_0 = 1;
    } else if (s[i] == '1') {
      has_1 = 1;
    } else {
      has_other = 1;
      break;
    }
  }
  if ((has_0 || has_1) && !has_other) {
    return "YES";
  } else {
    return "NO";
  }
}