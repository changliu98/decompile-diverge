int __cdecl func0(int n)
{
  if (!n)
    return 0;

  int msb = 0;
  for (int temp = n / 2; temp > 0; temp /= 2)
    ++msb;

  return 1 << msb;
}