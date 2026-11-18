void rotr(int *a,int *b,int *c)

{
  int iVar1;
  int temp;
  int *c_local;
  int *b_local;
  int *a_local;
  
  iVar1 = *a;
  *a = *c;
  *c = *b;
  *b = iVar1;
  return;
}