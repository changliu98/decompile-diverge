int func0(int number)

{
  int i;
  int sum;
  int number_local;
  
  sum = 1;
  for (i = 2; i < number; i = i + 1) {
    if (number % i == 0) {
      sum = i + sum;
    }
  }
  return sum;
}