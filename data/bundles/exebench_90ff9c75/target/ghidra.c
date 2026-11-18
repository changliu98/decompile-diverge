void WordToHex(uint Number,char *String)

{
  char cVar1;
  uint Module;
  uint Temp;
  int i;
  char *String_local;
  uint Number_local;
  
  Temp = Number;
  for (i = 3; -1 < i; i = i + -1) {
    cVar1 = (char)(Temp & 0xf);
    if ((Temp & 0xf) < 10) {
      String[i] = cVar1 + '0';
    }
    else {
      String[i] = cVar1 + '7';
    }
    Temp = Temp >> 4 & 0xfff;
  }
  String[4] = '\0';
  return;
}