void swap(int *pa,int *pb)

{
  int iVar1;
  int tmp;
  int *pb_local;
  int *pa_local;
  
  iVar1 = *pa;
  *pa = *pb;
  *pb = iVar1;
  return;
}