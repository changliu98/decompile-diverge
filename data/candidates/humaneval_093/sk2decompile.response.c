void _vowel_encrypt(char *in, char *out) {
  int i, j;
  char c;
  for (i = 0; in[i]; i++) {
    c = in[i];
    if (isupper(c))
      c = toupper(c);
    else if (islower(c))
      c = tolower(c);
    for (j = 0; "AaEeIiOoUu\0"[j]; j++) {
      if (c == "AaEeIiOoUu\0"[j]) {
        if (j < 10) c += 2;
        break;
      }
    }
    out[i] = c;
  }
  out[i] = '\0';
}