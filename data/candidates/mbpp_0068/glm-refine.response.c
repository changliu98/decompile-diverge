bool __cdecl func0(int *A, int n)
{
  bool nonDecreasing = true;  // stays true if A[i] <= A[i+1] for all i
  bool nonIncreasing = true;  // stays true if A[i] >= A[i+1] for all i

  for (int i = 0; i < n - 1; ++i)
  {
    if (A[i] > A[i + 1])
      nonDecreasing = false;
    if (A[i] < A[i + 1])
      nonIncreasing = false;
  }

  return nonDecreasing || nonIncreasing;
}