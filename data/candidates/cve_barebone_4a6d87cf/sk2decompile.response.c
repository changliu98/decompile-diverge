static int jpc_dec_process_sod(jpc_dec_t *dec, jpc_pkt_t *pkt) {
  jpc_tile_t *tile;
  jas_stream_t *str;
  long pos;
  long rwcount;
  tile = dec->tile;
  if (!tile) return -1;
  if (tile->numcomp == 0) {
    if (!jpc_dec_cp_isvalid(tile->cp)) return -1;
    if (jpc_dec_cp_prepare(tile->cp)) return -1;
    if (jpc_dec_tileinit(dec, tile)) return -1;
  }
  if (dec->streamlist) {
    tile->ppxmstr = jpc_streamlist_remove(dec->streamlist, 0);
    if (!tile->ppxmstr) return -1;
  }
  if (tile->ppxstab) {
    if (!tile->ppxmstr) {
      tile->ppxmstr = jas_stream_memopen(0, 0);
      if (!tile->ppxmstr) return -1;
    }
    pos = jas_stream_tell(tile->ppxmstr);
    jas_stream_seek(tile->ppxmstr, 0, 2);
    if (jpc_pptstabwrite(tile->ppxmstr, tile->ppxstab)) return -1;
    jas_stream_seek(tile->ppxmstr, pos, 0);
    jpc_ppxstab_destroy(tile->ppxstab);
    tile->ppxstab = 0;
  }
  if (jas_get_debug_level() >= 10) jpc_dec_dump(dec);
  str = tile->ppxmstr ? tile->ppxmstr : dec->istr;
  if (jpc_dec_decodepkts(dec, str, dec->istr)) {
    jas_logerrorf("jpc_dec_decodepkts failed\n");
    return -1;
  }
  if (dec->tiledataend > 0) {
    rwcount = jas_stream_getrwcount(dec->istr);
    if (rwcount < dec->tiledataend) {
      pos = dec->tiledataend - rwcount;
      jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n", pos);
      while (pos--) {
        if (jas_stream_getc(dec->istr) == -1) {
          jas_logerrorf("read error\n");
          return -1;
        }
      }
    } else if (rwcount > dec->tiledataend) {
      jas_logwarnf("warning: not enough tile data (%lu bytes)\n",
                   rwcount - dec->tiledataend);
    }
  }
  if (tile->numcp && tile->numcomp == tile->numcp - 1) {
    if (jpc_dec_tiledecode(dec, tile)) return -1;
    jpc_dec_tilefini(dec, tile);
  }
  dec->tile = 0;
  tile->numcomp++;
  dec->numcp = 8;
  return 0;
}