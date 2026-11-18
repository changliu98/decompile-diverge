static int jpc_dec_process_sod(jpc_dec_t *dec, jpc_cblk_t *cblk)
{
 jpc_dec_tile_t *tile;
 int ret;

 tile = dec->tile;
 if (!tile) {
  ret = -1;
 } else if (!tile->numparts) {

  if (!jpc_dec_cp_isvalid(tile->cp)) {
   ret = -1;
  } else if (jpc_dec_cp_prepare(tile->cp)) {
   ret = -1;
  } else if (jpc_dec_tileinit(dec, tile)) {
   ret = -1;
  } else {
   ret = 0;
  }
 } else {

  jpc_stream_t *stream;
  long pos;
  long curoff;
  long n;
  unsigned char buf[1];

  if (dec->stream) {
   if (!(tile->stream = jpc_streamlist_remove(
     dec->streamlist, 0))) {
    ret = -1;
   }
  } else if (tile->ppxtab) {

   if (!tile->stream) {
    if (!(tile->stream = jas_stream_memopen(0, 0))) {
     ret = -1;
    }
   } else {
    pos = jas_stream_tell(tile->stream);
    jas_stream_seek(tile->stream, 0, 2);
    if (jpc_pptstabwrite(tile->stream, tile->ppxtab)) {
     ret = -1;
    } else {
     jas_stream_seek(tile->stream, pos, 0);
     jpc_ppxstab_destroy(tile->ppxtab);
     tile->ppxtab = 0;
    }
   }

   if (jas_get_debug_level() >= 11) {
    jpc_dec_dump(dec);
   }

   if (tile->stream) {
    stream = tile->stream;
   } else {
    stream = dec->in;
   }
   if (jpc_dec_decodepkts(dec, stream, dec->in)) {
    jas_logerrorf("jpc_dec_decodepkts failed\n");
    ret = -1;
   } else if (dec->len > 0) {
    curoff = jas_stream_getrwcount(dec->in);
    if (curoff < dec->len) {
     n = dec->len - curoff;
     jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n",
       (unsigned long) n);
     while (n-- > 0) {
      if (jas_stream_getc(dec->in) == (-1)) {
       jas_logerrorf("read error\n");
       ret = -1;
      }
     }
    } else if (curoff > dec->len) {
     jas_logwarnf("warning: not enough tile data (%lu bytes)\n",
       (unsigned long) (curoff - dec->len));
    }
   } else if (tile->numdecodedparts < tile->numparts &&
     tile->numdecodedparts == tile->numparts - 1) {
    if (jpc_dec_tiledecode(dec, tile)) {
     ret = -1;
    } else {
     jpc_dec_tilefini(dec, tile);
    }
   }

   dec->tile = 0;
   ++tile->numdecodedparts;
   dec->state = 8;
   ret = 0;
  }
 }

 return ret;
}