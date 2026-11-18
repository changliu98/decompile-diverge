int __cdecl func0(int A, int B, int N)
{
  int v4; // [rsp+0h] [rbp-14h]

  if ( B - 1 >= N )
    v4 = N;
  else
    v4 = B - 1;
  return v4 * A / B;
}