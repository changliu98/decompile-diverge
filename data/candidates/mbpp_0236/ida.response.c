int __cdecl func0(int N, int K)
{
  if ( N >= K )
    return (N - 2 * K + 2) * (N - 2 * K + 1) / 2 + (N - K + 2) * (N - K + 1) / 2;
  else
    return -1;
}