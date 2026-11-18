int func0(int *lst, int size)
{
  int sum = 0;
  int largest = 0;
  int i;
  for (i = 0; i < size; i++) {
    int num = lst[i];
    int j;
    int is_prime = 1;
    for (j = 2; j * j <= num; j++) {
      if (num % j == 0) {
        is_prime = 0;
        break;
      }
    }
    if (is_prime && num > 1) {
      if (num > largest) {
        largest = num;
      }
    }
  }
  while (largest > 0) {
    sum += largest % 10;
    largest /= 10;
  }
  return sum;
}