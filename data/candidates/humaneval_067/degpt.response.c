int func0(char *s,int n)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ushort **ppuVar4;
  int i;
  int j;
  int is12;
  char num2 [10];
  char num1 [10];
  int n_local;
  char *s_local;
  
  memset(num1,0,10);
  memset(num2,0,10);
  bVar1 = false;
  j = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    ppuVar4 = __ctype_b_loc();
    if (((*ppuVar4)[(int)s[i]] & 0x800) == 0) {
      if ((!bVar1) && (0 < j)) {
        bVar1 = true;
        j = 0;
      }
    }
    else {
      if (bVar1) {
        num2[j] = s[i];
      }
      else {
        num1[j] = s[i];
      }
      j = j + 1;
    }
  }
  iVar2 = atoi(num1);
  iVar3 = atoi(num2);
  return (n - iVar2) - iVar3;
}