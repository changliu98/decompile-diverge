void func0(int a,int b,int *out,int *size)

{
  int iVar1;
  int i;
  int m;
  int *size_local;
  int *out_local;
  int b_local;
  int a_local;
  
  *size = 0;
  b_local = b;
  a_local = a;
  if (b < a) {
    b_local = a;
    a_local = b;
  }
  for (i = a_local; i <= b_local; i = i + 1) {
    if ((i < 10) && (i % 2 == 0)) {
      iVar1 = *size;
      *size = iVar1 + 1;
      out[iVar1] = i;
    }
  }
  return;
}