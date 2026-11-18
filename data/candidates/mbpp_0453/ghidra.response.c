int func0(int n)

{
  double dVar1;
  int curr_term;
  int curr_sum;
  int count;
  int i;
  int res;
  int n_local;
  undefined4 local_c;
  
  if (n % 2 == 0) {
    res = 1;
    i = 2;
    n_local = n;
    while( true ) {
      dVar1 = sqrt((double)n_local);
      if ((int)dVar1 + 1 < i) break;
      count = 0;
      curr_sum = 1;
      curr_term = 1;
      while (n_local % i == 0) {
        count = count + 1;
        n_local = n_local / i;
        if ((i == 2) && (count == 1)) {
          curr_sum = 0;
        }
        curr_term = curr_term * i;
        curr_sum = curr_sum + curr_term;
      }
      res = res * curr_sum;
      i = i + 1;
    }
    if (1 < n_local) {
      res = res * (n_local + 1);
    }
    local_c = res;
  }
  else {
    local_c = 0;
  }
  return local_c;
}