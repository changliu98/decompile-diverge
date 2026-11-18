_Bool func0(char *text)

{
  size_t sVar1;
  int i;
  int len;
  char *text_local;
  
  sVar1 = strlen(text);
  i = 0;
  while( true ) {
    if ((int)sVar1 / 2 <= i) {
      return true;
    }
    if (text[i] != text[((int)sVar1 + -1) - i]) break;
    i = i + 1;
  }
  return false;
}