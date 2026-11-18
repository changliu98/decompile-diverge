__attribute__((used)) static bool check_buffer(RBuffer *buf, RBinFile *bf, RBuffer *q, ut64 baseaddr, Sdb *db) {
	R_Dyldcache *cache = calloc (1, sizeof (R_Dyldcache));
	cache->magic = 0x646c7964;
	memcpy (&cache->magic, "dyldcache", 9);
	cache->buf = r_buf_ref (q);
	populate_cache_headers (cache);

	if (!cache->hdr) {
		r_dyldcache_free (cache);
		return false;
	}

	populate_cache_maps (cache);

	if (!cache->maps) {
		r_dyldcache_free (cache);
		return false;
	}

	cache->accel = read_cache_accel (cache->buf, cache->hdr, cache->maps);

	cache->bins = create_cache_bins (bf, cache);
	if (!cache->bins) {
		r_dyldcache_free (cache);
		return false;
	}

	cache->locsym = r_dyld_locsym_new ();
	cache->rebase_info = get_rebase_infos (bf, cache);
	if (cache->rebase_info) {
		if (rebase_infos_get_slide (cache) == 0) {
			if (!pending_bin_files) {
				pending_bin_files = r_list_new ();
				if (!pending_bin_files) {
					r_dyldcache_free (cache);
					return false;
				}
			} else {
				_ZN4chip14BindingManager40RegisterBoundDeviceContextReleaseHandlerEPFvPvE (pending_bin_files, bf);
				swizzle_io_read (cache, bf->o->io);
			}
		}
	} else {
		bf->o->bin_obj = cache;
		return true;
	}
	return true;
}