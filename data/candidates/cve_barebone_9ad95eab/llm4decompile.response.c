RzDyldRebaseInfos *get_rebase_infos(RzDyldCache *cache) {
	RzDyldRebaseInfos *result = calloc(1, sizeof(RzDyldRebaseInfos));
	if (!result) {
		return NULL;
	}
	if (cache->hdr->slideInfoOffset && cache->hdr->slideInfoSize && cache->hdr->mappingCount > 1) {
		RzDyldRebaseInfosEntry *infos = calloc(1, sizeof(RzDyldRebaseInfosEntry));
		if (!infos) {
			free (result);
			return NULL;
		}
		infos->start = cache->maps[1].fileOffset;
		infos->end = infos->start + cache->maps[1].size;
		infos->info = get_rebase_info(cache, cache->hdr->slideInfoOffset, cache->hdr->slideInfoSize, infos->start, -1);
		result->entries = infos;
		result->length = 1;
		return result;
	}
	ut32 n_slide_infos[16];
	ut32 total_slide_infos = 0;
	for (ut32 i = 0; i < cache->n_hdr && i < 16; i++) {
		ut64 hdr_offset = cache->hdr_offset[i];
		if (!rz_buf_read_le32_at (cache->buf, hdr_offset + 0x13c, &n_slide_infos[i])) {
			free (result);
			return NULL;
		}
		total_slide_infos += n_slide_infos[i];
	}
	if (!total_slide_infos) {
		free (result);
		return NULL;
	}
	RzDyldRebaseInfosEntry *infos = calloc(total_slide_infos, sizeof(RzDyldRebaseInfosEntry));
	if (!infos) {
		free (result);
		return NULL;
	}
	ut32 k = 0;
	for (ut32 i = 0; i < cache->n_hdr && i < 16; i++) {
		ut64 hdr_offset = cache->hdr_offset[i];
		if (!n_slide_infos[i]) {
			continue;
		}
		ut32 slide_infos_offset;
		if (!rz_buf_read_le32_at (cache->buf, hdr_offset + 0x138, &slide_infos_offset)) {
			free (result);
			return NULL;
		}
		if (!slide_infos_offset) {
			continue;
		}
		ut64 offset = hdr_offset + slide_infos_offset;
		RzDyldRebaseInfo *prev_info = NULL;
		for (ut32 j = 0; j < n_slide_infos[i]; j++) {
			cache_mapping_slide entry;
			if (rz_buf_fread_at (cache->buf, offset + j * sizeof(cache_mapping_slide), (ut8 *)&entry, "6lii", 1) != sizeof(cache_mapping_slide)) {
				break;
			}
			if (!entry.slideInfoOffset || !entry.slideInfoSize) {
				continue;
			}
			infos[k].start = hdr_offset + entry.fileOffset;
			infos[k].end = infos[k].start + entry.size;
			infos[k].info = get_rebase_info(cache, hdr_offset + entry.slideInfoOffset, entry.slideInfoSize, infos[k].start, prev_info ? prev_info->slide : -1);
			prev_info = infos[k].info;
			k++;
		}
	}
	if (!k) {
		free (infos);
		free (result);
		return NULL;
	}
	if (k < total_slide_infos) {
		RzDyldRebaseInfosEntry *pruned_infos = calloc(k, sizeof(RzDyldRebaseInfosEntry));
		if (!pruned_infos) {
			free (infos);
			free (result);
			return NULL;
		}
		memcpy(pruned_infos, infos, k * sizeof(RzDyldRebaseInfosEntry));
		free (infos);
		infos = pruned_infos;
	}
	result->entries = infos;
	result->length = k;
	return result;
}