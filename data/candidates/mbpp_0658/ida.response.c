int __cdecl func0(int *list1, int length)
{
  int j; // [rsp+0h] [rbp-20h]
  int occu; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]
  int result; // [rsp+Ch] [rbp-14h]
  int max_val; // [rsp+10h] [rbp-10h]

  max_val = 0;
  result = *list1;
  for ( i = 0; i < length; ++i )
  {
    occu = 0;
    for ( j = 0; j < length; ++j )
    {
      if ( list1[j] == list1[i] )
        ++occu;
    }
    if ( occu > max_val )
    {
      max_val = occu;
      result = list1[i];
    }
  }
  return result;
}