void swap(int *a,int *b)

{
  uint uVar1;
  uint uVar2;
  int *b_local;
  int *a_local;
  
  uVar2 = *b;
  uVar1 = *a;
  *a = uVar2 ^ uVar1;
  uVar2 = uVar2 ^ uVar1 ^ *b;
  *b = uVar2;
  *a = uVar2 ^ *a;
  return;
}