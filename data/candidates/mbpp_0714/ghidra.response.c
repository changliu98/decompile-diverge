int func0(int n)

{
  int j;
  int temp;
  int total;
  int i;
  int count;
  int m;
  int n_local;
  
  count = 0;
  n_local = n;
  for (i = 2; i * i <= n; i = i + 1) {
    total = 0;
    for (; n_local % i == 0; n_local = n_local / i) {
      total = total + 1;
    }
    j = 1;
    temp = 0;
    while (temp + j <= total) {
      count = count + 1;
      temp = j + temp;
      j = j + 1;
    }
  }
  if (n_local != 1) {
    count = count + 1;
  }
  return count;
}