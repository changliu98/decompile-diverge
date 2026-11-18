int getSum(int a, int b)
{
  int distance = abs(a - b);
  int sum = 0;
  while (distance > 0)
  {
    sum += distance % 10;
    distance /= 10;
  }
  return sum;
}