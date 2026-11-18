int __cdecl gd2GetHeader(
        gdIOCtxPtr in,
        int *sx,
        int *sy,
        int *cs_0,
        int *vers,
        int *fmt,
        int *ncx,
        int *ncy,
        t_chunk_info **chunkIdx)
{
  int nc; // [rsp+8h] [rbp-58h]
  t_chunk_info *cidx; // [rsp+10h] [rbp-50h]
  char id[5]; // [rsp+1Bh] [rbp-45h] BYREF
  int ch_0; // [rsp+20h] [rbp-40h]
  int i; // [rsp+24h] [rbp-3Ch]
  int *fmta; // [rsp+28h] [rbp-38h]
  int *versa; // [rsp+30h] [rbp-30h]
  int *cs_0a; // [rsp+38h] [rbp-28h]
  int *sya; // [rsp+40h] [rbp-20h]
  int *sxa; // [rsp+48h] [rbp-18h]
  gdIOCtxPtr ina; // [rsp+50h] [rbp-10h]

  ina = in;
  sxa = sx;
  sya = sy;
  cs_0a = cs_0;
  versa = vers;
  fmta = fmt;
  for ( i = 0; i < 4; ++i )
  {
    ch_0 = gdGetC(ina);
    if ( ch_0 == -1 )
      return 0;
    id[i] = ch_0;
  }
  id[4] = 0;
  if ( !strcmp(id, "gd2")
    && gdGetWord(versa, ina) == 1
    && (*versa == 1 || *versa == 2)
    && gdGetWord(sxa, ina)
    && gdGetWord(sya, ina)
    && gdGetWord(cs_0a, ina) == 1
    && *cs_0a >= 64
    && *cs_0a <= 4096
    && gdGetWord(fmta, ina) == 1
    && (*fmta == 1 || *fmta == 2 || *fmta == 3 || *fmta == 4)
    && gdGetWord(ncx, ina) == 1
    && gdGetWord(ncy, ina) == 1 )
  {
    if ( *fmta != 2 && *fmta != 4 )
      return 1;
    nc = *ncy * *ncx;
    if ( !overflow2(8, nc) && 8 * nc > 0 )
    {
      cidx = (t_chunk_info *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(8 * nc, 1uLL);
      if ( cidx )
      {
        for ( i = 0; ; ++i )
        {
          if ( i >= nc )
          {
            *chunkIdx = cidx;
            return 1;
          }
          if ( gdGetInt((int *)&cidx[i], ina) != 1
            || gdGetInt(&cidx[i].size, ina) != 1
            || cidx[i].offset < 0
            || cidx[i].size < 0 )
          {
            break;
          }
        }
        gdFree(cidx);
      }
    }
  }
  return 0;
}