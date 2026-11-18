void func0(char *text,char *out)

{
  size_t sVar1;
  int iVar2;
  int i;
  int j;
  int space_len;
  char *out_local;
  char *text_local;
  
  space_len = 0;
  j = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(text);
    if (sVar1 <= (ulong)(long)i) break;
    if (text[i] == ' ') {
      space_len = space_len + 1;
    }
    else {
      if (space_len == 1) {
        out[j] = '_';
        j = j + 1;
      }
      if (space_len == 2) {
        iVar2 = j + 1;
        out[j] = '_';
        j = j + 2;
        out[iVar2] = '_';
      }
      if (2 < space_len) {
        out[j] = '-';
        j = j + 1;
      }
      space_len = 0;
      out[j] = text[i];
      j = j + 1;
    }
    i = i + 1;
  }
  if (space_len == 1) {
    out[j] = '_';
    j = j + 1;
  }
  if (space_len == 2) {
    iVar2 = j + 1;
    out[j] = '_';
    j = j + 2;
    out[iVar2] = '_';
  }
  if (2 < space_len) {
    out[j] = '-';
    j = j + 1;
  }
  out[j] = '\0';
  return;
}