int __cdecl func0(int *list1, int size)
{
  int i_0; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]
  int first_odd; // [rsp+8h] [rbp-14h]
  int first_even; // [rsp+Ch] [rbp-10h]

  first_even = -1;
  first_odd = -1;
  for ( i = 0; i < size; ++i )
  {
    if ( !(list1[i] % 2) )
    {
      first_even = list1[i];
      break;
    }
  }
  for ( i_0 = 0; i_0 < size; ++i_0 )
  {
    if ( list1[i_0] % 2 )
    {
      first_odd = list1[i_0];
      return first_even - first_odd;
    }
  }
  return first_even - first_odd;
}