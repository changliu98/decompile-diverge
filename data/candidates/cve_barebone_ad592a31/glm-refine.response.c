bool __cdecl load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb)
{
  RDyldCache *cache = (RDyldCache *)calloc(1uLL, 0x78uLL);
  
  // "dyld_v1" in ASCII
  *(_DWORD *)cache->magic = 'dyld';
  *(_WORD *)&cache->magic[4] = '_v';
  cache->magic[6] = '1';
  
  cache->buf = r_buf_ref(buf);
  populate_cache_headers(cache);
  if ( !cache->hdr )
    goto cleanup_fail;
    
  populate_cache_maps(cache);
  if ( !cache->maps )
    goto cleanup_fail;
    
  cache->accel = read_cache_accel(cache->buf, cache->hdr, cache->maps);
  cache->bins = create_cache_bins(bf, cache);
  if ( !cache->bins )
    goto cleanup_fail;
    
  cache->locsym = r_dyld_locsym_new(cache);
  cache->rebase_infos = get_rebase_infos(bf, cache);
  
  if ( !cache->rebase_infos || rebase_infos_get_slide(cache) )
  {
success:
    *bin_obj = cache;
    return true;
  }
  
  if ( pending_bin_files || (pending_bin_files = r_list_new()) != NULL )
  {
    chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(pending_bin_files, bf);
    swizzle_io_read(cache, bf->rbin->iob.io);
    goto success;
  }

cleanup_fail:
  r_dyldcache_free(cache);
  return false;
}