bool __cdecl contains_even_number(int *arr, int n)
{
  for (int i = 0; i < n; ++i)
  {
    if ((arr[i] & 1) == 0)
      return true;
  }
  return false;
}