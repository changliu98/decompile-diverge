void __cdecl descending2(int *a, int *b)
{
  int temp; // [rsp+0h] [rbp-14h]

  temp = *a;
  if ( *a < *b )
  {
    *a = *b;
    *b = temp;
  }
}