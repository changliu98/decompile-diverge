int foo(float *dists,int k)

{
  int k_local;
  float *dists_local;
  int local_c;
  
  local_c = k;
  if (0.0 < *dists != 0.0 < dists[1]) {
    local_c = 0;
  }
  return local_c;
}