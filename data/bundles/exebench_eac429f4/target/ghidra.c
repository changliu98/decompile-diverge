void exchange(int *pint1,int *pint2)

{
  int iVar1;
  int temp;
  int *pint2_local;
  int *pint1_local;
  
  iVar1 = *pint1;
  *pint1 = *pint2;
  *pint2 = iVar1;
  return;
}