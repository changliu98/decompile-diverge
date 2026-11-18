bool __cdecl load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb)
{
  RDyldCache *cache; // [rsp+8h] [rbp-38h]

  cache = (RDyldCache *)calloc(1uLL, 0x78uLL);
  *(_DWORD *)cache->magic = 1684830564;
  *(_WORD *)&cache->magic[4] = 24931;
  cache->magic[6] = 99;
  cache->buf = r_buf_ref(buf);
  populate_cache_headers(cache);
  if ( !cache->hdr )
    goto LABEL_9;
  populate_cache_maps(cache);
  if ( !cache->maps )
    goto LABEL_9;
  cache->accel = read_cache_accel(cache->buf, cache->hdr, cache->maps);
  cache->bins = create_cache_bins(bf, cache);
  if ( !cache->bins )
    goto LABEL_9;
  cache->locsym = r_dyld_locsym_new(cache);
  cache->rebase_infos = get_rebase_infos(bf, cache);
  if ( !cache->rebase_infos || rebase_infos_get_slide(cache) )
  {
LABEL_11:
    *bin_obj = cache;
    return 1;
  }
  if ( pending_bin_files || (pending_bin_files = r_list_new()) != 0LL )
  {
    chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(pending_bin_files, bf);
    swizzle_io_read(cache, bf->rbin->iob.io);
    goto LABEL_11;
  }
LABEL_9:
  r_dyldcache_free(cache);
  return 0;
}