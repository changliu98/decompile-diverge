int func0(int n) {
  int i, sum, temp;
  temp = n;
  if (temp % 2 == 0) {
    printf("Invalid Input\n");
    return -1;
  }
  sum = 0;
  i = 0;
  while (temp >= 1) {
    i++;
    sum = sum + temp;
    temp = temp - 2;
  }
  sum = sum / i;
  return sum;
}