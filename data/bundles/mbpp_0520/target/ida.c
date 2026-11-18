int __cdecl func0(int *l, int size)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int lcm; // [rsp+8h] [rbp-18h]

  lcm = find_lcm(*l, l[1]);
  for ( i = 2; i < size; ++i )
    lcm = find_lcm(lcm, l[i]);
  return lcm;
}