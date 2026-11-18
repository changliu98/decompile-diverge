int __cdecl func0(int *arr, int lens, int n)
{
  int result = 1;
  for (int i = 0; i < lens; ++i)
    result = (arr[i] * result) % n;
  return result;
}