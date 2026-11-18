int sprint_int_number_nonlocalized(char *str,int q,int minimum,int sign)

{
  bool bVar1;
  int iVar2;
  int base;
  int j;
  int i;
  int z;
  int flag;
  int sign_local;
  int minimum_local;
  int q_local;
  char *str_local;
  
  base = 1000000000;
  minimum_local = minimum;
  if (minimum < 0) {
    minimum_local = 0;
  }
  bVar1 = 9 < minimum_local;
  if (q < 0) {
    j = 1;
    *str = '-';
    q_local = -q;
  }
  else {
    if (sign != 0) {
      *str = '+';
    }
    j = (int)(sign != 0);
    q_local = q;
  }
  for (i = 10; i != 0; i = i + -1) {
    if (minimum_local == i) {
      bVar1 = true;
    }
    iVar2 = q_local / base;
    q_local = q_local % base;
    if ((iVar2 != 0) || (bVar1)) {
      str[j] = (char)iVar2 + '0';
      bVar1 = true;
      j = j + 1;
    }
    base = base / 10;
  }
  if (!bVar1) {
    str[j] = '0';
    j = j + 1;
  }
  str[j] = '\0';
  return j;
}