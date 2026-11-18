void ceasar(char *text,char offset)

{
  int j;
  uint i;
  char offset_local;
  char *text_local;
  
  for (i = 0; text[i] != '\0'; i = i + 1) {
    if ((('@' < text[i]) && (text[i] < '[')) || (('`' < text[i] && (text[i] < '{')))) {
      for (j = 0; j < offset; j = j + 1) {
        if (text[i] == 'Z') {
          text[i] = 'A';
          text[i] = text[i] + -1;
        }
        if (text[i] == 'z') {
          text[i] = 'a';
          text[i] = text[i] + -1;
        }
        text[i] = text[i] + '\x01';
      }
    }
  }
  return;
}