static bool load_buffer(RCore *core, void **user, RBuffer *b, ut64 loadaddr,
                        Sdb *sdb) {
  RDyldCache *cache = calloc(1, sizeof(RDyldCache));
  cache->magic[0] = 'c';
  cache->magic[1] = 'a';
  cache->magic[2] = 'c';
  cache->magic[3] = 'h';
  cache->magic[4] = 'e';
  cache->magic[5] = 'd';
  cache->magic[6] = 'a';
  cache->magic[7] = 't';
  cache->magic[8] = 'a';
  cache->magic[9] = 'b';
  cache->magic[10] = 'l';
  cache->magic[11] = 'e';
  cache->buf = r_buf_ref(b);
  populate_cache_headers(cache);
  if (!cache->accel_data) {
    goto fail;
  }
  populate_cache_maps(cache);
  if (!cache->accel_map) {
    goto fail;
  }
  cache->accel =
      read_cache_accel(cache->buf, cache->accel_data, cache->accel_map);
  cache->bins = create_cache_bins(core, cache);
  if (!cache->bins) {
    goto fail;
  }
  cache->locsym = r_dyld_locsym_new(cache);
  cache->rebase_infos = get_rebase_infos(core, cache);
  if (cache->rebase_infos && rebase_infos_get_slide(cache) == 0) {
    if (!bound_device_context_release_handlers) {
      bound_device_context_release_handlers = r_list_new();
      if (!bound_device_context_release_handlers) {
        goto fail;
      }
    }
    chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(
        bound_device_context_release_handlers, core);
    swizzle_io_read(cache, core->io->desc.fd);
  }
  *user = cache;
  return true;
fail:
  r_dyldcache_free(cache);
  return false;
}