int __cdecl func0(int A, int N, int L, int R)
{
  int max_count = R - L + 1;
  int count = max_count - (R / A) - (L - 1) / A;

  if (count > N)
    count = N;

  if (count <= 0)
    return R + 1;

  return L + count + (L - 1) / A;
}