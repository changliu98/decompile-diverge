int test_and_set(int *target)

{
  int iVar1;
  int rv;
  int *target_local;
  
  iVar1 = *target;
  *target = 1;
  return iVar1;
}