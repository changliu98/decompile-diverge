void array_are_reference_type(int *arr)

{
  int iVar1;
  int tmp;
  int *arr_local;
  
  iVar1 = *arr;
  *arr = arr[1];
  arr[1] = iVar1;
  return;
}