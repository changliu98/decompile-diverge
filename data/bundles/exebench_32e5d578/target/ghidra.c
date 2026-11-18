void intToBin(uint n,int *binary)

{
  int i;
  uint mask;
  int *binary_local;
  uint n_local;
  
  n_local = n;
  for (i = 0; i < 8; i = i + 1) {
    binary[i] = (uint)((n_local & 0x80) != 0);
    n_local = n_local << 1;
  }
  return;
}