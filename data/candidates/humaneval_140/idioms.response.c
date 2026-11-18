void func0(char *in, char *out)
{
  int i;
  int j = 0;
  int space_len = 0;
  for (i = 0; i < strlen(in); i++) {
    if (in[i] == ' ') {
      space_len++;
    }
    else {
      if (space_len == 1) {
        out[j++] = '_';
      }
      if (space_len == 2) {
        out[j++] = '_';
        out[j++] = '_';
      }
      if (space_len > 2) {
        out[j++] = '-';
      }
      space_len = 0;
      out[j++] = in[i];
    }
  }
  if (space_len == 1) {
    out[j++] = '_';
  }
  if (space_len == 2) {
    out[j++] = '_';
    out[j++] = '_';
  }
  if (space_len > 2) {
    out[j++] = '-';
  }
  out[j] = '\0';
}