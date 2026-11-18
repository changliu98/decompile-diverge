void rotr(int *a,int *b,int *c)

{
  int iVar1;
  int num;
  int *c_local;
  int *b_local;
  int *a_local;
  
  iVar1 = *c;
  *c = *b;
  *b = *a;
  *a = iVar1;
  return;
}