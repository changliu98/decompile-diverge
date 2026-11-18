int func0(int n)

{
  int iVar1;
  double dVar2;
  int n_local;
  
  iVar1 = n + 1;
  dVar2 = log2((double)iVar1);
  dVar2 = log2((double)iVar1 + dVar2);
  return iVar1 + (int)dVar2;
}