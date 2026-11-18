char *__cdecl func0(int *arr, int n, int p)
{
  int i; // [rsp+0h] [rbp-20h]
  int _sum; // [rsp+4h] [rbp-1Ch]

  _sum = 0;
  for ( i = 0; i < n; ++i )
    _sum += arr[i];
  if ( p != 1 )
    return "EVEN";
  if ( _sum % 2 )
    return "EVEN";
  return (char *)&unk_2004;
}