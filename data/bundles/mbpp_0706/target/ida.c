bool __cdecl func0(int *arr1, int m, int *arr2, int n)
{
  int i_0; // [rsp+8h] [rbp-418h]
  int i; // [rsp+Ch] [rbp-414h]
  bool hashset[1000]; // [rsp+10h] [rbp-410h] BYREF
  int na; // [rsp+3FCh] [rbp-24h]
  int *arr2a; // [rsp+400h] [rbp-20h]
  int ma; // [rsp+40Ch] [rbp-14h]
  int *arr1a; // [rsp+410h] [rbp-10h]

  arr1a = arr1;
  ma = m;
  arr2a = arr2;
  na = n;
  memset(hashset, 0, sizeof(hashset));
  for ( i = 0; i < ma; ++i )
    hashset[arr1a[i]] = 1;
  for ( i_0 = 0; i_0 < na; ++i_0 )
  {
    if ( !hashset[arr2a[i_0]] )
      return 0;
  }
  return 1;
}