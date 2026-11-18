void _convert_to_c_identifier(char *str, char *c_id) {
  int i, j, spaces;
  spaces = 0;
  j = 0;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == ' ') {
      spaces++;
    } else {
      if (spaces == 1) {
        c_id[j++] = '_';
      }
      if (spaces == 2) {
        c_id[j++] = '_';
        c_id[j++] = '_';
      }
      if (spaces > 2) {
        c_id[j++] = '-';
      }
      spaces = 0;
      c_id[j++] = str[i];
    }
  }
  if (spaces == 1) {
    c_id[j++] = '_';
  }
  if (spaces == 2) {
    c_id[j++] = '_';
    c_id[j++] = '_';
  }
  if (spaces > 2) {
    c_id[j++] = '-';
  }
  c_id[j] = '\0';
}