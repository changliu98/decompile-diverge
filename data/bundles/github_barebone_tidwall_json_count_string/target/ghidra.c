size_t count_string(uint8_t *raw,uint8_t *end,int *infoout)

{
  size_t sVar1;
  bool bVar2;
  _Bool e;
  int info;
  size_t i;
  size_t len;
  int *infoout_local;
  uint8_t *end_local;
  uint8_t *raw_local;
  
  i = 1;
  info = 0;
  bVar2 = false;
  while (i + 8 <= (ulong)((long)end - (long)raw)) {
    sVar1 = i;
    if (""[raw[i]] == '\0') {
      bVar2 = false;
      sVar1 = i + 1;
      if (""[raw[i + 1]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 2;
      if (""[raw[i + 2]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 3;
      if (""[raw[i + 3]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 4;
      if (""[raw[i + 4]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 5;
      if (""[raw[i + 5]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 6;
      if (""[raw[i + 6]] != '\0') goto LAB_00106083;
      bVar2 = false;
      sVar1 = i + 7;
      if (""[raw[i + 7]] != '\0') goto LAB_00106083;
      bVar2 = false;
      i = i + 8;
    }
    else {
LAB_00106083:
      i = sVar1;
      if (raw[i] == '\"') {
        i = i + 1;
        if (!bVar2) {
LAB_001060f5:
          *infoout = info;
          return i;
        }
        bVar2 = false;
      }
      else {
        if (raw[i] == '\\') {
          info = 1;
          bVar2 = (bool)(bVar2 ^ 1);
        }
        i = i + 1;
      }
    }
  }
  while( true ) {
    if ((ulong)((long)end - (long)raw) < i + 1) goto LAB_001060f5;
    sVar1 = i;
    if (""[raw[i]] != '\0') break;
    bVar2 = false;
    i = i + 1;
  }
  goto LAB_00106083;
}