char *func0(char *text)
{
  int i = 0;
  int j = 0;
  char *out = (char *)malloc((strlen(text)+1)*sizeof(char));
  for (i = 0; text[i]; i++) {
    if (((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISalnum)) {
      out[j++] = text[i];
    }
  }
  out[j] = '\0';
  strcpy(text, out);
  return text;
}