int __cdecl func0(int n)
{
  int sum = 0;
  int sum_of_squares = 0;

  for (int i = 1; i <= n; ++i)
  {
    sum += i;
    sum_of_squares += i * i;
  }

  return sum * sum - sum_of_squares;
}