int jpc_dec_process_sod(jpc_dec_t *dec,jpc_ms_t *ms)

{
  jpc_dec_tile_t *tile_00;
  int iVar1;
  jas_stream_t *pjVar2;
  long lVar3;
  jas_stream_t *local_50;
  uint_fast32_t n;
  long curoff;
  int pos;
  jpc_dec_tile_t *tile;
  jpc_ms_t *ms_local;
  jpc_dec_t *dec_local;
  int local_c;
  
  tile_00 = dec->curtile;
  if (tile_00 == (jpc_dec_tile_t *)0x0) {
    return -1;
  }
  if (tile_00->partno == 0) {
    iVar1 = jpc_dec_cp_isvalid(tile_00->cp);
    if (iVar1 == 0) {
      return -1;
    }
    iVar1 = jpc_dec_cp_prepare(tile_00->cp);
    if (iVar1 != 0) {
      return -1;
    }
    iVar1 = jpc_dec_tileinit(dec,tile_00);
    if (iVar1 != 0) {
      return -1;
    }
  }
  if (dec->pkthdrstreams != (jpc_streamlist_t *)0x0) {
    pjVar2 = jpc_streamlist_remove(dec->pkthdrstreams,0);
    tile_00->pkthdrstream = pjVar2;
    if (pjVar2 == (jas_stream_t *)0x0) {
      return -1;
    }
  }
  if (tile_00->pptstab != (jpc_ppxstab_t *)0x0) {
    if (tile_00->pkthdrstream == (jas_stream_t *)0x0) {
      pjVar2 = jas_stream_memopen((char *)0x0,0);
      tile_00->pkthdrstream = pjVar2;
      if (pjVar2 == (jas_stream_t *)0x0) {
        return -1;
      }
    }
    lVar3 = jas_stream_tell(tile_00->pkthdrstream);
    jas_stream_seek(tile_00->pkthdrstream,0,2);
    iVar1 = jpc_pptstabwrite(tile_00->pkthdrstream,tile_00->pptstab);
    if (iVar1 != 0) {
      return -1;
    }
    jas_stream_seek(tile_00->pkthdrstream,(long)(int)lVar3,0);
    jpc_ppxstab_destroy(tile_00->pptstab);
    tile_00->pptstab = (jpc_ppxstab_t *)0x0;
  }
  iVar1 = jas_get_debug_level();
  if (9 < iVar1) {
    jpc_dec_dump(dec);
  }
  if (tile_00->pkthdrstream == (jas_stream_t *)0x0) {
    local_50 = dec->in;
  }
  else {
    local_50 = tile_00->pkthdrstream;
  }
  iVar1 = jpc_dec_decodepkts(dec,local_50,dec->in);
  if (iVar1 == 0) {
    if (0 < dec->curtileendoff) {
      lVar3 = jas_stream_getrwcount(dec->in);
      if (lVar3 < dec->curtileendoff) {
        n = dec->curtileendoff - lVar3;
        jas_logwarnf("warning: ignoring trailing garbage (%lu bytes)\n",n);
        while (n != 0) {
          iVar1 = jas_stream_getc(dec->in);
          n = n - 1;
          if (iVar1 == -1) {
            jas_logerrorf("read error\n");
            return -1;
          }
        }
      }
      else if (dec->curtileendoff < lVar3) {
        jas_logwarnf("warning: not enough tile data (%lu bytes)\n",lVar3 - dec->curtileendoff);
      }
    }
    if ((tile_00->numparts != 0) && (tile_00->partno == tile_00->numparts - 1)) {
      iVar1 = jpc_dec_tiledecode(dec,tile_00);
      if (iVar1 != 0) {
        return -1;
      }
      jpc_dec_tilefini(dec,tile_00);
    }
    dec->curtile = (jpc_dec_tile_t *)0x0;
    tile_00->partno = tile_00->partno + 1;
    dec->state = 8;
    local_c = 0;
  }
  else {
    jas_logerrorf("jpc_dec_decodepkts failed\n");
    local_c = -1;
  }
  return local_c;
}