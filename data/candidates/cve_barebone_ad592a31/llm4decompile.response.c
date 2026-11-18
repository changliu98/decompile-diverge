bool load_buffer(RBinFile *bf, void **bin_obj, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	RDyldCache *cache = calloc(1, sizeof(RDyldCache));
	cache->magic[0] = 'c';
	cache->magic[1] = 'a';
	cache->magic[2] = 'c';
	cache->magic[3] = 'h';
	cache->magic[4] = 'e';
	cache->magic[5] = 0x00;
	cache->magic[6] = 0x00;
	cache->buf = r_buf_ref(buf);
	populate_cache_headers(cache);
	if (!cache->hdr) {
		r_dyldcache_free(cache);
		return false;
	}
	populate_cache_maps(cache);
	if (!cache->maps) {
		r_dyldcache_free(cache);
		return false;
	}
	cache->accel = read_cache_accel(cache->buf, cache->hdr, cache->maps);
	cache->bins = create_cache_bins(bf, cache);
	if (!cache->bins) {
		r_dyldcache_free(cache);
		return false;
	}
	cache->locsym = r_dyld_locsym_new(cache);
	cache->rebase_infos = get_rebase_infos(bf, cache);
	if (cache->rebase_infos && rebase_infos_get_slide(cache) == 0) {
		if (!pending_bin_files) {
			pending_bin_files = r_list_new();
			if (!pending_bin_files) {
				r_dyldcache_free(cache);
				return false;
			}
		}
		r_list_push(pending_bin_files, bf);
		swizzle_io_read(cache, bf->rbin->iob.io);
	}
	*bin_obj = cache;
	return true;
}