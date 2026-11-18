char * func0(char *text)

{
  int i;
  char *text_local;
  
  for (i = 0; text[i] != '\0'; i = i + 1) {
    if (((text[i] == ' ') || (text[i] == ',')) || (text[i] == '.')) {
      text[i] = ':';
    }
  }
  return text;
}