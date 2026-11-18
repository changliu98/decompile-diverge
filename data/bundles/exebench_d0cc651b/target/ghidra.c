void increment(uint *n)

{
  uint w;
  uint x;
  uint *n_local;
  
  x = *n;
  w = 1;
  while ((x & w) != 0) {
    x = x ^ w;
    w = w << 1;
  }
  *n = x ^ w;
  return;
}