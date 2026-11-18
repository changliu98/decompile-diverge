int * func0(int n,int *size)

{
  int iVar1;
  int *piVar2;
  int i;
  int *out;
  int *size_local;
  int n_local;
  
  piVar2 = malloc(0x100);
  *size = 0;
  n_local = n;
  for (i = 2; i * i <= n_local; i = i + 1) {
    while (n_local % i == 0) {
      n_local = n_local / i;
      iVar1 = *size;
      *size = iVar1 + 1;
      piVar2[iVar1] = i;
    }
  }
  if (1 < n_local) {
    iVar1 = *size;
    *size = iVar1 + 1;
    piVar2[iVar1] = n_local;
  }
  return piVar2;
}