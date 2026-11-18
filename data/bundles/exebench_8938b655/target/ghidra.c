int itos(int i,char *s)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int ans;
  char c;
  int k;
  int j;
  int digit;
  char *s_local;
  int i_local;
  
  if (-1 < i) {
    k = -1;
    i_local = i;
  }
  else {
    k = 0;
    i_local = -i;
    *s = '-';
  }
  j = (int)(-1 >= i);
  iVar2 = k;
  do {
    k = iVar2;
    iVar3 = i_local % 10;
    i_local = i_local / 10;
    iVar2 = k + 1;
    s[iVar2] = (char)iVar3 + '0';
  } while (i_local != 0);
  s[k + 2] = '\0';
  iVar3 = k + 2;
  k = iVar2;
  for (; j < k; j = j + 1) {
    cVar1 = s[j];
    s[j] = s[k];
    s[k] = cVar1;
    k = k + -1;
  }
  return iVar3;
}