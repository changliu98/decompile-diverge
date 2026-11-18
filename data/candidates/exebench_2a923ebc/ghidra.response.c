void swap(int *p1,int *p2)

{
  int iVar1;
  int tmp;
  int *p2_local;
  int *p1_local;
  
  iVar1 = *p1;
  *p1 = *p2;
  *p2 = iVar1;
  return;
}