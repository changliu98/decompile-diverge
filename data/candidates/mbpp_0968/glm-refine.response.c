int __cdecl func0(int A, int B, int N)
{
  // Clamp the value of (B - 1) to a maximum of N
  int clamped_val = (B - 1 >= N) ? N : (B - 1);
  
  // Multiply by A, then divide by B
  return (clamped_val * A) / B;
}