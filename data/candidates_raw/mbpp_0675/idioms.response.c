int f(int x, int y, int m, int n){
  int z = x + y;
  if ( z < m || z > n){
    return z;
  }
  return 20;
}