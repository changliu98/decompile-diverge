int __cdecl func0(int n)
{
  size_t v1; // rax
  size_t k; // [rsp+8h] [rbp-58h]
  size_t j_0; // [rsp+10h] [rbp-50h]
  size_t j; // [rsp+18h] [rbp-48h]
  char y; // [rsp+27h] [rbp-39h]
  size_t z_len; // [rsp+28h] [rbp-38h]
  char z[11]; // [rsp+31h] [rbp-2Fh] BYREF
  int i; // [rsp+3Ch] [rbp-24h]
  size_t length; // [rsp+40h] [rbp-20h]
  char nums[11]; // [rsp+4Dh] [rbp-13h] BYREF
  int na; // [rsp+58h] [rbp-8h]

  na = n;
  sprintf(nums, "%d", (unsigned int)n);
  length = strlen(nums);
  for ( i = length - 2; ; --i )
  {
    if ( i < 0 )
      return 0;
    if ( nums[i] < nums[i + 1] )
      break;
  }
  strcpy(z, &nums[i]);
  z_len = strlen(z);
  y = z[1];
  for ( j = 1LL; j < z_len; ++j )
  {
    if ( z[j] > z[0] && z[j] < y )
      y = z[j];
  }
  for ( j_0 = 0LL; j_0 < z_len; ++j_0 )
  {
    if ( z[j_0] == y )
    {
      for ( k = j_0; k < z_len - 1; ++k )
        z[k] = z[k + 1];
      z[z_len - 1] = 0;
      break;
    }
  }
  v1 = strlen(z);
  qsort(z, v1, 1uLL, (__compar_fn_t)&strcmp);
  nums[i] = y;
  strcpy(&nums[i + 1], z);
  return atoi(nums);
}