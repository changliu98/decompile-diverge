void _Sort(int *p0,int *p1)

{
  int iVar1;
  int temp;
  int *p1_local;
  int *p0_local;
  
  if (*p1 < *p0) {
    iVar1 = *p0;
    *p0 = *p1;
    *p1 = iVar1;
  }
  return;
}