void __cdecl descending2(int *a, int *b)
{
  if (*a < *b)
  {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
}