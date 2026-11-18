int jpc_dec_process_sod(struct jpc_dec *dec, struct jpc_ms *ms)
{
  struct jpc_dec_tile *tile = dec->curtile;
  if (!tile)
    return -1;
  if (tile->partno == 0) {
    if (!jpc_dec_gettile(tile->cp))
      return -1;
    if (jpc_dec_gettileend(tile->cp))
      return -1;
    if (jpc_dec_gettileheader(dec, tile))
      return -1;
  }
  if (dec->pkthdrstreams) {
    tile->pkthdrstream = jpc_dec_getstream(dec->pkthdrstreams, 0);
    if (!tile->pkthdrstream)
      return -1;
  }
  if (tile->pptstab) {
    if (!tile->pkthdrstream) {
      tile->pkthdrstream = jpc_dec_getstream(((void *)0), 0);
      if (!tile->pkthdrstream)
        return -1;
    }
    int oldpos = jpc_stream_tell(tile->pkthdrstream);
    jpc_stream_seek(tile->pkthdrstream, 0, 2);
    if (jpc_dec_readpkthdr(tile->pkthdrstream, tile->pptstab))
      return -1;
    jpc_stream_seek(tile->pkthdrstream, oldpos, 0);
    jpc_dec_closepkthdr(tile->pptstab);
    tile->pptstab = ((void *)0);
  }
  if (jpc_dec_gettilecount() >= 10)
    jpc_dec_gettilecountreset(dec);
  struct jas_stream *stream = tile->pkthdrstream ? tile->pkthdrstream : dec->in;
  if (jpc_dec_decodepkts(dec, stream, dec->in)) {
    fprintf(stderr, "jpc_dec_decodepkts failed\n");
    return -1;
  }
  if (dec->curtileendoff > 0) {
    unsigned long off = jpc_stream_tell(dec->in);
    if (off < dec->curtileendoff) {
      unsigned long n = dec->curtileendoff - off;
      fprintf(stderr, "warning: ignoring trailing garbage (%lu bytes)\n", n);
      while (n--) {
        if (jpc_stream_readbyte(dec->in) == -1) {
          fprintf(stderr, "read error\n");
          return -1;
        }
      }
    }
    else if (off > dec->curtileendoff)
      fprintf(stderr, "warning: not enough tile data (%lu bytes)\n", off - dec->curtileendoff);
  }
  if (tile->numparts && tile->partno == tile->numparts - 1) {
    if (jpc_dec_gettilepart(dec, tile))
      return -1;
    jpc_dec_gettileend(dec, tile);
  }
  dec->curtile = ((void *)0);
  tile->partno++;
  dec->state = 8;
  return 0;
}