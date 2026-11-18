long func0(int M)

{
  int r;
  long lVar1;
  long b;
  long a;
  int n;
  int M_local;
  
  r = M / 2;
  lVar1 = bin_coff(r << 1,r);
  return lVar1 / (long)(r + 1);
}