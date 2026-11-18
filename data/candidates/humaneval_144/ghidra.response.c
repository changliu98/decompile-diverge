int func0(char *x,char *n)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char den [101];
  char num [101];
  int j;
  int i;
  int d;
  int c;
  int b;
  int a;
  char *n_local;
  char *x_local;
  uint local_c;
  
  for (i = 0; x[i] != '/'; i = i + 1) {
    num[i] = x[i];
  }
  num[i] = '\0';
  iVar1 = atoi(num);
  j = 0;
  while (i = i + 1, x[i] != '\0') {
    den[j] = x[i];
    j = j + 1;
  }
  den[j] = '\0';
  iVar2 = atoi(den);
  for (i = 0; n[i] != '/'; i = i + 1) {
    num[i] = n[i];
  }
  num[i] = '\0';
  iVar3 = atoi(num);
  j = 0;
  while (i = i + 1, n[i] != '\0') {
    den[j] = n[i];
    j = j + 1;
  }
  den[j] = '\0';
  iVar4 = atoi(den);
  local_c = (uint)((iVar1 * iVar3) % (iVar2 * iVar4) == 0);
  return local_c;
}