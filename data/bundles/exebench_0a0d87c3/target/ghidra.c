void swap(int *param1,int *param2)

{
  int iVar1;
  int buffer;
  int *param2_local;
  int *param1_local;
  
  iVar1 = *param1;
  *param1 = *param2;
  *param2 = iVar1;
  return;
}