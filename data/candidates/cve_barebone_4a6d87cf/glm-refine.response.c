define JPC_DEC_STATE_MAIN 8

int __cdecl jpc_dec_process_sod(jpc_dec_t *dec, jpc_ms_t *ms)
{
  jpc_dec_tile_t *tile;
  jas_stream_t *in;
  long curoff;
  uint_fast32_t n;

  if (!dec || !dec->curtile)
    return -1;
  tile = dec->curtile;

  // Initialize tile on the first part
  if (!tile->partno) {
    if (!jpc_dec_cp_isvalid(tile->cp) ||
        jpc_dec_cp_prepare(tile->cp) ||
        jpc_dec_tileinit(dec, tile)) {
      return -1;
    }
  }

  // Assign packet header stream from the list if available
  if (dec->pkthdrstreams) {
    tile->pkthdrstream = jpc_streamlist_remove(dec->pkthdrstreams, 0);
    if (!tile->pkthdrstream)
      return -1;
  }

  // Append PPT marker table data to the packet header stream
  if (tile->pptstab) {
    if (!tile->pkthdrstream) {
      tile->pkthdrstream = jas_stream_memopen(0LL, 0);
      if (!tile->pkthdrstream)
        return -1;
    }
    int pos = jas_stream_tell(tile->pkthdrstream);
    jas_stream_seek(tile->pkthdrstream, 0LL, SEEK_END); // 2 = SEEK_END
    if (jpc_pptstabwrite(tile->pkthdrstream, tile->pptstab))
      return -1;
    jas_stream_seek(tile->pkthdrstream, pos, SEEK_SET); // 0 = SEEK_SET
    jpc_ppxstab_destroy(tile->pptstab);
    tile->pptstab = 0LL;
  }

  if (jas_get_debug_level() >= 10)
    jpc_dec_dump(dec);

  // Select the appropriate input stream for decoding packets
  in = tile->pkthdrstream ? tile->pkthdrstream : dec->in;

  if (jpc_dec_decodepkts(dec, in, dec->in) != 0) {
    jas_logerrorf("jpc_dec_decodepkts failed\n");
    return -1;
  }

  // Handle tile data bounds and trailing garbage
  if (dec->curtileendoff > 0) {
    curoff = jas_stream_getrwcount(dec->in);
    if (curoff > dec->curtileendoff) {
      jas_logwarnf("warning: not enough tile data (%lu bytes)\n", curoff - dec->curtileendoff);
    } else if (curoff < dec->curtileendoff) {
      n = dec->curtileendoff - curoff;
      jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n", n);
      while (n--) {
        if (jas_stream_getc(dec->in) == -1) {
          jas_logerrorf("read error\n");
          return -1;
        }
      }
    }
  }

  // Finalize tile decoding if it's the last part
  if (tile->numparts && tile->partno == tile->numparts - 1) {
    if (jpc_dec_tiledecode(dec, tile))
      return -1;
    jpc_dec_tilefini(dec, tile);
  }

  dec->curtile = 0LL;
  ++tile->partno;
  dec->state = JPC_DEC_STATE_MAIN;

  return 0;
}