int __cdecl func0(int N)
{
  double sqrt_N = sqrt((double)N);
  int floor_sqrt = (int)floor(sqrt_N);
  return (floor_sqrt + 1) * (floor_sqrt + 1);
}