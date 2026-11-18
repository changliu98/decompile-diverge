void unhide(char *text)

{
  int i;
  int iOile [3];
  int iPrzes;
  char *text_local;
  
  iPrzes = 0;
  iOile._0_8_ = DAT_00102004;
  iOile[2] = DAT_0010200c;
  for (i = 0; text[i] != '\0'; i = i + 1) {
    text[i] = text[i] - (char)iOile[iPrzes];
    iPrzes = iPrzes + 1;
    if (iPrzes == 3) {
      iPrzes = 0;
    }
  }
  return;
}