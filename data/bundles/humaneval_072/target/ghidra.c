_Bool func0(int *q,int size,int w)

{
  int i;
  int sum;
  int w_local;
  int size_local;
  int *q_local;
  
  sum = 0;
  i = 0;
  while( true ) {
    if (size / 2 <= i) {
      if (size % 2 == 1) {
        sum = q[size / 2] + sum;
      }
      return sum <= w;
    }
    if (q[i] != q[(size + -1) - i]) break;
    sum = q[i] + q[(size + -1) - i] + sum;
    i = i + 1;
  }
  return false;
}