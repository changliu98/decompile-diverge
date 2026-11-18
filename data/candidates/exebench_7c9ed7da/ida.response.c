void __cdecl swap(int *i, int *j)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *j;
  *j = *i;
  *i = temp;
}