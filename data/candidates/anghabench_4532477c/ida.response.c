char *__cdecl unmakemask(int mask, char *smask)
{
  int v2; // ecx
  int v3; // ecx
  int i; // [rsp+0h] [rbp-14h]

  i = 0;
  if ( (LUA_MASKCALL & mask) != 0 )
  {
    i = 1;
    *smask = 99;
  }
  if ( (LUA_MASKRET & mask) != 0 )
  {
    v2 = i++;
    smask[v2] = 114;
  }
  if ( (LUA_MASKLINE & mask) != 0 )
  {
    v3 = i++;
    smask[v3] = 108;
  }
  smask[i] = 0;
  return smask;
}