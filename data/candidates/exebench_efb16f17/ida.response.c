unsigned int __cdecl ether_hash(unsigned __int8 *ea)
{
  int i; // [rsp+0h] [rbp-10h]
  unsigned int hash; // [rsp+4h] [rbp-Ch]

  hash = 0;
  for ( i = 0; i < 6; ++i )
    hash = (hash << 16) + (hash << 6) + ea[i] - hash;
  return hash;
}