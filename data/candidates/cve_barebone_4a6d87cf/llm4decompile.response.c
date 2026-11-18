int jpc_dec_process_sod(jpc_dec_t *dec, jpc_ms_t *ms)
{
 jpc_dec_tile_t *tile;
 jas_stream_t *in;
 int ret;

 tile = dec->curtile;
 if (!tile)
  return -1;

 if (tile->partno == 0) {
  if (!jpc_dec_cp_isvalid(tile->cp))
   return -1;
  if (jpc_dec_cp_prepare(tile->cp))
   return -1;
  if (jpc_dec_tileinit(dec, tile))
   return -1;
 }

 if (dec->pkthdrstreams) {
  tile->pkthdrstream = jpc_streamlist_remove(dec->pkthdrstreams, 0);
  if (!tile->pkthdrstream)
   return -1;
 }

 if (tile->pptstab) {
  int pos;
  if (!tile->pkthdrstream) {
   tile->pkthdrstream = jas_stream_memopen((char *) 0, 0);
   if (!tile->pkthdrstream)
    return -1;
  }
  pos = jas_stream_tell(tile->pkthdrstream);
  jas_stream_seek(tile->pkthdrstream, 0, 2);
  ret = jpc_pptstabwrite(tile->pkthdrstream, tile->pptstab);
  if (ret)
   return -1;
  jas_stream_seek(tile->pkthdrstream, pos, 0);
  jpc_ppxstab_destroy(tile->pptstab);
  tile->pptstab = 0;
 }

 if (jas_get_debug_level() >= 10)
  jpc_dec_dump(dec);

 in = tile->pkthdrstream ? tile->pkthdrstream : dec->in;

 ret = jpc_dec_decodepkts(dec, in, dec->in);
 if (ret) {
  jas_logerrorf("jpc_dec_decodepkts failed\n");
  return -1;
 }

 if (dec->curtileendoff > 0) {
  long rwcount;
  rwcount = jas_stream_getrwcount(dec->in);
  if (rwcount < dec->curtileendoff) {
   unsigned long len;
   len = dec->curtileendoff - rwcount;
   jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n",
    len);
   while (len--) {
    if (jas_stream_getc(dec->in) == -1) {
     jas_logerrorf("read error\n");
     return -1;
    }
   }
  } else if (rwcount > dec->curtileendoff) {
   jas_logwarnf("warning: not enough tile data (%lu bytes)\n",
    rwcount - dec->curtileendoff);
  }
 }

 if (tile->numparts && tile->partno == tile->numparts - 1) {
  if (jpc_dec_tiledecode(dec, tile))
   return -1;
  jpc_dec_tilefini(dec, tile);
 }

 dec->curtile = 0;
 tile->partno++;
 dec->state = 8;

 return 0;
}