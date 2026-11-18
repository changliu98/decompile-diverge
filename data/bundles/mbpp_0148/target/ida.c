int __cdecl func0(int N)
{
  int v2; // [rsp+4h] [rbp-Ch]
  int A; // [rsp+8h] [rbp-8h]

  A = closest(N);
  v2 = sum_digits_single(A);
  return sum_digits_single(N - A) + v2;
}