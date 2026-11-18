int itoa(char *a,int i)

{
  ulong uVar1;
  int local_30;
  int j;
  int abs_i;
  int temp;
  int charc;
  int i_local;
  char *a_local;
  int local_c;
  
  if (i == 0) {
    *a = '0';
    a[1] = '\0';
    local_c = 2;
  }
  else {
    charc = 0;
    temp = 1;
    local_30 = i;
    if (i < 0) {
      local_30 = -i;
    }
    for (; local_30 % temp != local_30; temp = temp * 10) {
      charc = charc + 1;
    }
    if (i < 0) {
      charc = charc + 1;
    }
    temp = 1;
    j = charc;
    while (j = j + -1, -1 < j) {
      uVar1 = (long)(local_30 - local_30 % temp) / (long)temp;
      a[j] = (char)((long)((ulong)(uint)((int)uVar1 >> 0x1f) << 0x20 | uVar1 & 0xffffffff) % 10) +
             '0';
      temp = temp * 10;
    }
    if (i < 0) {
      *a = '-';
    }
    a[charc] = '\0';
    local_c = charc;
  }
  return local_c;
}