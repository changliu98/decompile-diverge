int conv_hstring(char *string,uint *num)

{
  bool bVar1;
  int pos;
  uint *num_local;
  char *string_local;
  
  pos = 0;
  *num = 0;
  while( true ) {
    if ((('/' < string[pos]) && (string[pos] < ':')) ||
       ((bVar1 = false, '`' < string[pos] && (bVar1 = false, string[pos] < 'g')))) {
      bVar1 = pos < 9;
    }
    if (!bVar1) break;
    if ((string[pos] < '0') || ('9' < string[pos])) {
      *num = (*num * 0x10 + (int)string[pos]) - 0x57;
    }
    else {
      *num = *num * 0x10 + string[pos] + -0x30;
    }
    pos = pos + 1;
  }
  return pos;
}