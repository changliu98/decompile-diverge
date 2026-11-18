int __cdecl jpc_dec_process_sod(jpc_dec_t *dec, jpc_ms_t *ms)
{
  jas_stream_t *v2; // rax
  jas_stream_t *v3; // rax
  jas_stream_t *in; // [rsp+8h] [rbp-48h]
  uint_fast32_t n; // [rsp+18h] [rbp-38h]
  long curoff; // [rsp+20h] [rbp-30h]
  int pos; // [rsp+2Ch] [rbp-24h]
  jpc_dec_tile_t *tile; // [rsp+30h] [rbp-20h]

  tile = dec->curtile;
  if ( !dec->curtile )
    return -1;
  if ( !tile->partno )
  {
    if ( !jpc_dec_cp_isvalid(tile->cp) )
      return -1;
    if ( jpc_dec_cp_prepare(tile->cp) )
      return -1;
    if ( jpc_dec_tileinit(dec, tile) )
      return -1;
  }
  if ( dec->pkthdrstreams )
  {
    v2 = jpc_streamlist_remove(dec->pkthdrstreams, 0);
    tile->pkthdrstream = v2;
    if ( !v2 )
      return -1;
  }
  if ( tile->pptstab )
  {
    if ( !tile->pkthdrstream )
    {
      v3 = jas_stream_memopen(0LL, 0);
      tile->pkthdrstream = v3;
      if ( !v3 )
        return -1;
    }
    pos = jas_stream_tell(tile->pkthdrstream);
    jas_stream_seek(tile->pkthdrstream, 0LL, 2);
    if ( jpc_pptstabwrite(tile->pkthdrstream, tile->pptstab) )
      return -1;
    jas_stream_seek(tile->pkthdrstream, pos, 0);
    jpc_ppxstab_destroy(tile->pptstab);
    tile->pptstab = 0LL;
  }
  if ( jas_get_debug_level() >= 10 )
    jpc_dec_dump(dec);
  if ( tile->pkthdrstream )
    in = tile->pkthdrstream;
  else
    in = dec->in;
  if ( !jpc_dec_decodepkts(dec, in, dec->in) )
  {
    if ( dec->curtileendoff > 0 )
    {
      curoff = jas_stream_getrwcount(dec->in);
      if ( curoff >= dec->curtileendoff )
      {
        if ( curoff > dec->curtileendoff )
          jas_logwarnf("warning: not enough tile data (%lu bytes)\n", curoff - dec->curtileendoff);
      }
      else
      {
        n = dec->curtileendoff - curoff;
        jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n", n);
        while ( n-- )
        {
          if ( jas_stream_getc(dec->in) == -1 )
          {
            jas_logerrorf("read error\n");
            return -1;
          }
        }
      }
    }
    if ( tile->numparts && tile->partno == tile->numparts - 1 )
    {
      if ( jpc_dec_tiledecode(dec, tile) )
        return -1;
      jpc_dec_tilefini(dec, tile);
    }
    dec->curtile = 0LL;
    ++tile->partno;
    dec->state = 8;
    return 0;
  }
  jas_logerrorf("jpc_dec_decodepkts failed\n");
  return -1;
}