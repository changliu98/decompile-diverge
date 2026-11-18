int prot2perm(int x)

{
  int r;
  int x_local;
  
  r = 0;
  if ((x & 1U) != 0) {
    r = 4;
  }
  if ((x & 2U) != 0) {
    r = r | 2;
  }
  if ((x & 4U) != 0) {
    r = r | 1;
  }
  return r;
}