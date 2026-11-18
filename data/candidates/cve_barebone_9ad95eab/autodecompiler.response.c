__attribute__((used)) static RList *get_rebase_infos(RebaseCache *cache) {
	RList *ret = calloc (1, sizeof (RList));
	if (!ret) {
		return NULL;
	}
	if (!cache->ctx->slide_info_offset || !cache->ctx->slide_info_size) {
		ut32 n_slide_infos[16];
		ut32 total_slide_infos = 0;
		unsigned int i = 0;
		for (;;) {
			if (i >= cache->n_segments || i >= 16) {
				break;
			}
			ut64 hdr_offset = cache->segments[i].vmaddr;
			if (!rz_buf_read_le32_at (cache->buf, hdr_offset + 0x13c, &n_slide_infos[i])) {
				goto beach;
			}
			total_slide_infos += n_slide_infos[i];
			i++;
		}
		if (!total_slide_infos) {
			goto beach;
		}
		RebaseInfo *infos = calloc (total_slide_infos, sizeof (RebaseInfo));
		if (!infos) {
			goto beach;
		}
		unsigned int k = 0;
		i = 0;
		for (;;) {
			if (i >= cache->n_segments || i >= 16) {
				break;
			}
			ut64 hdr_offset = cache->segments[i].vmaddr;
			if (!n_slide_infos[i]) {
				continue;
			}
			ut32 slide_infos_offset;
			if (!rz_buf_read_le32_at (cache->buf, hdr_offset + 0x138, &slide_infos_offset)) {
				continue;
			}
			if (!slide_infos_offset) {
				continue;
			}
			slide_infos_offset += hdr_offset;
			RebaseInfo *prev_info = NULL;
			unsigned int j;
			for (j = 0; j < n_slide_infos[i]; j++) {
				ut64 slide_info_offset = slide_infos_offset + j * 0x38;
				CacheMappingSlide entry;
				if (rz_buf_fread_at (cache->buf, slide_info_offset, (ut8 *)&entry, "6lii", 1) != 0x38) {
					break;
				}
				if (!entry.slideInfoOffset || !entry.slideInfoSize) {
					continue;
				}
				infos[k].data_offset = hdr_offset + entry.fileOffset;
				infos[k].data_len = entry.size;
				ut64 slide_base_offset = prev_info? prev_info->data_len: -1;
				infos[k].rebase_info = get_rebase_info (cache, hdr_offset + entry.slideInfoOffset, entry.slideInfoSize, infos[k].data_offset, slide_base_offset);
				prev_info = &infos[k];
				k++;
			}
			i++;
		}
		if (!k) {
			free (infos);
			goto beach;
		}
		if (k < total_slide_infos) {
			RebaseInfo *tmp = realloc (infos, k * sizeof (RebaseInfo));
			if (!tmp) {
				free (infos);
				goto beach;
			}
			infos = tmp;
		}
		ret->head = infos;
		ret->length = k;
	} else {
		if (cache->ctx->page_start > 1) {
			RebaseInfo *info = calloc (1, sizeof (RebaseInfo));
			if (!info) {
				goto beach;
			}
			info->data_offset = cache->ctx->page_start;
			info->data_len = info->data_offset + cache->ctx->page_size;
			info->rebase_info = get_rebase_info (cache, cache->ctx->slide_info_offset, cache->ctx->slide_info_size, info->data_offset, -1);
			ret->head = info;
			ret->length = 1;
		}
	}
	return ret;
beach:
	free (ret);
	return NULL;
}