char *func0(char *text)
{
  char *new_text = ((void *)0);
  unsigned long text_len = strlen(text);
  int i = 0; int j = 0;
  new_text = (char *)malloc(text_len * 2);
  for (i = 0; i < text_len; i++) {
    if ((i > 0 && ((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISupper) && (((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISlower) || ((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISpunct))
     || (i > 0 && ((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISupper) && ((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISupper)
     && ((*__ctype_b_loc ())[(int) ((text[i + 1]))] & (unsigned short) _ISlower))) {
      new_text[j++] = '_';
      new_text[j++] = tolower(text[i]);
    } else {
      new_text[j++] = tolower(text[i]);
    }
  }
  new_text[j] = '\0';
  return new_text;
}