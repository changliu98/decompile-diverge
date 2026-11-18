int func0(int n,int p)

{
  int i;
  int out;
  int p_local;
  int n_local;
  
  out = 1;
  for (i = 0; i < n; i = i + 1) {
    out = (out << 1) % p;
  }
  return out;
}