void SwitchToChar(char *str,uchar data)

{
  uchar data_local;
  char *str_local;
  
  if (data / 0x10 < 10) {
    *str = data / 0x10 + 0x30;
  }
  else {
    *str = data / 0x10 + 0x37;
  }
  if ((uint)data % 0x10 < 10) {
    str[1] = data % 0x10 + 0x30;
  }
  else {
    str[1] = data % 0x10 + 0x37;
  }
  return;
}