int func0(char *text)

{
  size_t sVar1;
  int i;
  int len;
  char *text_local;
  int local_c;
  
  sVar1 = strlen(text);
  len = (int)sVar1;
  for (text_local = text; *text_local == ' '; text_local = text_local + 1) {
    len = len + -1;
  }
  if (len < 1) {
    local_c = -1;
  }
  else if ((*text_local == '+') || (*text_local == '-')) {
    for (i = 1; i < len; i = i + 1) {
      if ((text_local[i] < '0') || ('9' < text_local[i])) {
        return 0;
      }
    }
    local_c = 1;
  }
  else {
    for (i = 0; i < len; i = i + 1) {
      if ((text_local[i] < '0') || ('9' < text_local[i])) {
        return 0;
      }
    }
    local_c = 1;
  }
  return local_c;
}