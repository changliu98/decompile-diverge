int __cdecl func0(int *list1, int n)
{
  int i; // [rsp+0h] [rbp-18h]
  int first_odd; // [rsp+4h] [rbp-14h]
  int first_even; // [rsp+8h] [rbp-10h]

  first_even = -1;
  first_odd = -1;
  for ( i = 0; i < n; ++i )
  {
    if ( !(list1[i] % 2) && first_even == -1 )
      first_even = list1[i];
    if ( list1[i] % 2 && first_odd == -1 )
      first_odd = list1[i];
    if ( first_even != -1 && first_odd != -1 )
      break;
  }
  return first_odd * first_even;
}