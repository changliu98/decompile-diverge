bool __cdecl func0(int A, int B)
{
  // Loop as long as both A and B are strictly greater than 0
  while (A > 0 && B > 0)
  {
    A /= 10;
    B /= 10;
  }

  // Return true if both A and B became 0, false otherwise
  return A == 0 && B == 0;
}