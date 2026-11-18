void sort_three(int *v1,int *v2,int *v3)

{
  int iVar1;
  int tmp;
  int *v3_local;
  int *v2_local;
  int *v1_local;
  
  if (*v2 < *v1) {
    iVar1 = *v2;
    *v2 = *v1;
    *v1 = iVar1;
  }
  if (*v3 < *v1) {
    iVar1 = *v3;
    *v3 = *v1;
    *v1 = iVar1;
  }
  if (*v3 < *v2) {
    iVar1 = *v2;
    *v2 = *v3;
    *v3 = iVar1;
  }
  return;
}