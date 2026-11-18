void __cdecl swap(int *i, int *j)
{
  int temp = *j;
  *j = *i;
  *i = temp;
}