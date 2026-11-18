int c_decrypt(char *text)

{
  int c;
  char *text_local;
  
  for (text_local = text; *text_local != '\0'; text_local = text_local + 1) {
    c = *text_local + -0xd;
    if (c < 1) {
      c = *text_local + 0xf3;
    }
    *text_local = (char)c;
  }
  return 0;
}