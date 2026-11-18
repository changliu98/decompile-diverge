int __cdecl func0(int A, int B, int N)
{
  // Clamp the upper bound to N, but do not exceed B - 1
  int bound = (B - 1 <= N) ? N : B - 1;
  
  // Scale A by the computed bound and divide by B
  return (bound * A) / B;
}