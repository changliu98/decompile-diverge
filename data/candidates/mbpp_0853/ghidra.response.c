/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(int n)

{
  double dVar1;
  int curr_term;
  int curr_sum;
  int count;
  int i;
  int res;
  int n_local;
  
  res = 1;
  for (n_local = n; n_local % 2 == 0; n_local = n_local / 2) {
  }
  i = 3;
  while( true ) {
    dVar1 = sqrt((double)n_local);
    if (dVar1 + _DAT_00102008 < (double)i) break;
    curr_sum = 1;
    curr_term = 1;
    for (; n_local % i == 0; n_local = n_local / i) {
      curr_term = i * curr_term;
      curr_sum = curr_term + curr_sum;
    }
    res = curr_sum * res;
    i = i + 2;
  }
  if (1 < n_local) {
    res = (n_local + 1) * res;
  }
  return res;
}