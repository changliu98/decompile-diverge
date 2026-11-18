int __cdecl do_bid_note(
        magic_set *ms,
        unsigned __int8 *nbuf,
        uint32_t type,
        int swap,
        uint32_t namesz,
        uint32_t descsz,
        size_t noff,
        size_t doff,
        int *flags)
{
  int v9; // eax
  uint32_t i; // [rsp+4h] [rbp-4Ch]
  uint8_t desc[20]; // [rsp+10h] [rbp-40h] BYREF
  uint32_t descsza; // [rsp+28h] [rbp-28h]
  uint32_t namesza; // [rsp+2Ch] [rbp-24h]
  int swapa; // [rsp+30h] [rbp-20h]
  uint32_t typea; // [rsp+34h] [rbp-1Ch]
  unsigned __int8 *nbufa; // [rsp+38h] [rbp-18h]
  magic_set *msa; // [rsp+40h] [rbp-10h]

  msa = ms;
  nbufa = nbuf;
  typea = type;
  swapa = swap;
  namesza = namesz;
  descsza = descsz;
  if ( namesz != 4 || strcmp((const char *)&nbufa[noff], s2) || typea != 3 )
    return 0;
  *flags |= 0x10u;
  switch ( descsza )
  {
    case 8u:
      v9 = file_printf(msa, ", BuildID[%s]=", "xxHash");
      break;
    case 0x10u:
      v9 = file_printf(msa, ", BuildID[%s]=", "md5/uuid");
      break;
    case 0x14u:
      v9 = file_printf(msa, ", BuildID[%s]=", "sha1");
      break;
    default:
      v9 = file_printf(msa, ", BuildID[%s]=", "unknown");
      break;
  }
  if ( v9 == -1 )
    return 1;
  memcpy(desc, &nbufa[doff], descsza);
  for ( i = 0; i < descsza; ++i )
  {
    if ( file_printf(msa, "%02x", desc[i]) == -1 )
      return 1;
  }
  return 1;
}