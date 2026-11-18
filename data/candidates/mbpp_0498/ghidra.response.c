int func0(int x,int y)

{
  int k;
  int gcd;
  int y_local;
  int x_local;
  int local_c;
  
  gcd = 1;
  local_c = y;
  if (x % y != 0) {
    for (k = y / 2; 0 < k; k = k + -1) {
      if ((x % k == 0) && (y % k == 0)) {
        gcd = k;
        break;
      }
    }
    local_c = gcd;
  }
  return local_c;
}