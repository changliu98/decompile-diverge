int decToBin(int n,int *binary)

{
  int iVar1;
  int y;
  uint x;
  uint i;
  int *binary_local;
  int n_local;
  
  x = 0;
  for (i = 1; i <= (uint)n; i = i << 1) {
    x = x + 1;
  }
  iVar1 = x - 1;
  n_local = n;
  for (y = iVar1; i = i >> 1, -1 < y; y = y + -1) {
    if ((int)(n_local - i) < 0) {
      binary[iVar1 - y] = 0;
    }
    else {
      n_local = n_local - i;
      binary[iVar1 - y] = 1;
    }
  }
  return iVar1;
}