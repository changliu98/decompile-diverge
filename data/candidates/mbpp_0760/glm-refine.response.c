const char *__cdecl func0(int *arr, int n)
{
  for (int i = 1; i < n; ++i)
  {
    if (arr[i] != arr[0])
      return "False"; // &unk_2004
  }
  return "True"; // &unk_2007
}