int __cdecl func0(int N)
{
  int A = closest(N);
  return sum_digits_single(A) + sum_digits_single(N - A);
}