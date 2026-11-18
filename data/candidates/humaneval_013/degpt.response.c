int func0(int a,int b)

{
  int iVar1;
  int m;
  int b_local;
  int a_local;
  
  b_local = b;
  a_local = a;
  while (b_local != 0) {
    iVar1 = a_local % b_local;
    a_local = b_local;
    b_local = iVar1;
  }
  return a_local;
}