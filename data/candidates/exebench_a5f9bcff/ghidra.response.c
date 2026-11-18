int foo(int *p1,int *p2)

{
  int iVar1;
  int iVar2;
  int *p2_local;
  int *p1_local;
  
  iVar1 = *p1;
  *p1 = iVar1 + 1;
  iVar2 = *p2;
  *p2 = iVar2 + 1;
  return iVar1 + iVar2;
}