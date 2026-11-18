void ui2a(uint num,uint base,int uc,char *bf)

{
  char cVar1;
  uint uVar2;
  int dgt;
  uint d;
  int n;
  char *bf_local;
  int uc_local;
  uint base_local;
  uint num_local;
  
  n = 0;
  for (d = 1; bf_local = bf, num_local = num, base <= num / d; d = base * d) {
  }
  while (d != 0) {
    uVar2 = num_local / d;
    num_local = num_local % d;
    d = d / base;
    if (((n != 0) || (0 < (int)uVar2)) || (d == 0)) {
      if ((int)uVar2 < 10) {
        cVar1 = '0';
      }
      else {
        cVar1 = 'a';
        if (uc != 0) {
          cVar1 = 'A';
        }
        cVar1 = cVar1 + -10;
      }
      *bf_local = (char)uVar2 + cVar1;
      n = n + 1;
      bf_local = bf_local + 1;
    }
  }
  *bf_local = '\0';
  return;
}