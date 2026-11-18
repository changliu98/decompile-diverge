int func0(int a,int b)

{
  int local_20;
  int i;
  int sum;
  int b_local;
  int a_local;
  
  sum = 0;
  i = 1;
  while( true ) {
    local_20 = b;
    if (a < b) {
      local_20 = a;
    }
    if (local_20 <= i) break;
    if ((a % i == 0) && (b % i == 0)) {
      sum = i + sum;
    }
    i = i + 1;
  }
  return sum;
}