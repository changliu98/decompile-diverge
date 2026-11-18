_Bool load_buffer(RBinFile *bf,void **bin_obj,RBuffer *buf,ut64 loadaddr,Sdb *sdb)

{
  RDyldCache *cache_00;
  RBuffer *pRVar1;
  cache_accel_t *pcVar2;
  RList *pRVar3;
  RDyldLocSym *pRVar4;
  RDyldRebaseInfos *pRVar5;
  ut64 uVar6;
  RDyldCache *cache;
  Sdb *sdb_local;
  ut64 loadaddr_local;
  RBuffer *buf_local;
  void **bin_obj_local;
  RBinFile *bf_local;
  _Bool local_9;
  
  cache_00 = calloc(1,0x78);
  *(undefined4 *)cache_00->magic = DAT_001030b3;
  *(undefined2 *)(cache_00->magic + 4) = DAT_001030b7;
  cache_00->magic[6] = DAT_001030b9;
  pRVar1 = r_buf_ref(buf);
  cache_00->buf = pRVar1;
  populate_cache_headers(cache_00);
  if (cache_00->hdr == (cache_hdr_t *)0x0) {
    r_dyldcache_free(cache_00);
    local_9 = false;
  }
  else {
    populate_cache_maps(cache_00);
    if (cache_00->maps == (cache_map_t *)0x0) {
      r_dyldcache_free(cache_00);
      local_9 = false;
    }
    else {
      pcVar2 = read_cache_accel(cache_00->buf,cache_00->hdr,cache_00->maps);
      cache_00->accel = pcVar2;
      pRVar3 = create_cache_bins(bf,cache_00);
      cache_00->bins = pRVar3;
      if (cache_00->bins == (RList *)0x0) {
        r_dyldcache_free(cache_00);
        local_9 = false;
      }
      else {
        pRVar4 = r_dyld_locsym_new(cache_00);
        cache_00->locsym = pRVar4;
        pRVar5 = get_rebase_infos(bf,cache_00);
        cache_00->rebase_infos = pRVar5;
        if ((cache_00->rebase_infos != (RDyldRebaseInfos *)0x0) &&
           (uVar6 = rebase_infos_get_slide(cache_00), uVar6 == 0)) {
          if ((pending_bin_files == (RList *)0x0) &&
             (pending_bin_files = r_list_new(), pending_bin_files == (RList *)0x0)) {
            r_dyldcache_free(cache_00);
            return false;
          }
          r_list_push(pending_bin_files,bf);
          swizzle_io_read(cache_00,(bf->rbin->iob).io);
        }
        *bin_obj = cache_00;
        local_9 = true;
      }
    }
  }
  return local_9;
}