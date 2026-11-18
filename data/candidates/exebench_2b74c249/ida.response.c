int __cdecl setsize(unsigned __int64 capacity, unsigned int *cyls, unsigned int *hds, unsigned int *secs)
{
  __int64 cylinders; // [rsp+8h] [rbp-40h]
  unsigned __int64 sectors; // [rsp+10h] [rbp-38h]
  unsigned __int64 heads; // [rsp+18h] [rbp-30h]
  int rv; // [rsp+24h] [rbp-24h]

  rv = 0;
  cylinders = 1024LL;
  LODWORD(sectors) = 62;
  heads = capacity / 0xF800;
  if ( capacity % 0xF800 )
  {
    sectors = capacity / (++heads << 10);
    if ( capacity % (heads << 10) )
      cylinders = capacity / (++sectors * heads);
  }
  if ( !cylinders )
    rv = -1;
  *cyls = cylinders;
  *secs = sectors;
  *hds = heads;
  return rv;
}