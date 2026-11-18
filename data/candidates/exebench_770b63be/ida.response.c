void __cdecl decrease_order(int *num1, int *diff)
{
  int tmp; // [rsp+0h] [rbp-14h]

  if ( *num1 < *diff )
  {
    tmp = *num1;
    *num1 = *diff;
    *diff = tmp;
  }
}