int func0(int num)

{
  int i;
  int sum;
  int num_local;
  
  sum = 0;
  num_local = num;
  for (i = 2; i * i <= num_local; i = i + 1) {
    for (; num_local % i == 0; num_local = num_local / i) {
      sum = i + sum;
    }
  }
  return num_local + sum;
}