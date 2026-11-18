int __cdecl computesizes(int *nums, int *narray)
{
  int n; // [rsp+4h] [rbp-24h]
  int na; // [rsp+8h] [rbp-20h]
  int a; // [rsp+Ch] [rbp-1Ch]
  int twotoi; // [rsp+10h] [rbp-18h]
  int i; // [rsp+14h] [rbp-14h]

  a = 0;
  na = 0;
  n = 0;
  i = 0;
  for ( twotoi = 1; twotoi / 2 < *narray; twotoi *= 2 )
  {
    if ( nums[i] > 0 )
    {
      a += nums[i];
      if ( a > twotoi / 2 )
      {
        n = twotoi;
        na = a;
      }
    }
    if ( a == *narray )
      break;
    ++i;
  }
  *narray = n;
  return na;
}