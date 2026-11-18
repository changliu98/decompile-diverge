uint sgl_len(uint n)

{
  uint n_local;
  
  return ((n - 1) * 3 >> 1) + (n - 1 & 1) + 2;
}