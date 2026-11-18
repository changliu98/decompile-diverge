struct RzDyldRebaseInfos *get_rebase_infos(struct RzDyldCache *cache)
{
  struct RzDyldRebaseInfos *rebase_infos = ((void *)0);
  struct RzDyldRebaseInfosEntry *infos = ((void *)0);
  struct RzDyldRebaseInfosEntry *pruned_infos = ((void *)0);
  struct RzDyldRebaseInfo *rebase_info = ((void *)0);
  struct RzDyldRebaseInfo *prev_rebase_info = ((void *)0);
  struct cache_mapping_slide slide;
  struct cache_mapping_slide *slide_infos = ((void *)0);
  unsigned int i;
  unsigned int n_slide_infos[16];
  unsigned int total_slide_infos = 0;
  unsigned int n_slide_infos_idx = 0;
  unsigned int slide = 0;
  unsigned int slide_idx = 0;
  unsigned int offset = 0;
  unsigned int file_offset = 0;
  unsigned int slide_infos_offset = 0;
  unsigned int slide_idx_offset = 0;
  if ((rebase_infos = calloc(1, sizeof *rebase_infos)) == ((void *)0))
    return ((void *)0);
  if (cache->hdr->slideInfoOffset == 0 || cache->hdr->slideInfoSize == 0) {
    for (i = 0; i < cache->n_hdr; i++) {
      if (i >= (sizeof n_slide_infos / sizeof n_slide_infos[0]))
        break;
      if (rz_buf_read_le32_at(cache->buf,
          cache->hdr_offset[i] + (sizeof *cache->hdr) / sizeof(unsigned int),
          &n_slide_infos[i]) == 0)
        goto fail;
      total_slide_infos += n_slide_infos[i];
    }
    if (total_slide_infos == 0)
      goto fail;
    if ((infos = calloc(total_slide_infos, sizeof *infos)) == ((void *)0))
      goto fail;
    for (n_slide_infos_idx = 0, i = 0;
         i < cache->n_hdr;
         i++) {
      if (i >= (sizeof n_slide_infos / sizeof n_slide_infos[0]))
        break;
      if (n_slide_infos[i] == 0)
        continue;
      if (rz_buf_read_le32_at(cache->buf,
          cache->hdr_offset[i] + (sizeof *cache->hdr) / sizeof(unsigned int) - 4,
          &slide_idx_offset) == 0)
        break;
      if (slide_idx_offset == 0)
        continue;
      slide_idx_offset += cache->hdr_offset[i];
      if (rz_buf_read_le32_at(cache->buf,
          slide_idx_offset,
          &slide_idx) == 0)
        break;
      if (slide_idx == 0)
        continue;
      slide_idx_offset += sizeof slide_idx;
      for (slide_idx = 0;
           slide_idx < n_slide_infos[i];
           slide_idx++) {
        if (rz_buf_fread_at(cache->buf,
            slide_idx * sizeof slide,
            (char *)&slide + (slide_idx * sizeof slide),
            "6lii",
            1) != sizeof slide)
          break;
        if (slide.slideInfoOffset == 0 ||
            slide.slideInfoSize == 0)
          continue;
        infos[n_slide_infos_idx].start =
          cache->hdr_offset[i] + slide.fileOffset;
        infos[n_slide_infos_idx].end =
          infos[n_slide_infos_idx].start + slide.size;
        if (prev_rebase_info == ((void *)0))
          slide = -1;
        else
          slide = prev_rebase_info->slide;
        rebase_info = get_rebase_info(cache,
                                      cache->hdr_offset[i] +
                                      slide.slideInfoOffset,
                                      slide.slideInfoSize,
                                      cache->hdr_offset[i] +
                                      slide.fileOffset,
                                      slide);
        infos[n_slide_infos_idx].info = rebase_info;
        prev_rebase_info = infos[n_slide_infos_idx].info;
      }
    }
    if (n_slide_infos_idx == 0)
      goto fail_free_infos;
    if (n_slide_infos_idx < total_slide_infos) {
      if ((pruned_infos = calloc(n_slide_infos_idx, sizeof *pruned_infos)) == ((void *)0))
        goto fail_free_infos;
      memcpy(pruned_infos, infos,
             n_slide_infos_idx * sizeof *pruned_infos);
      free(infos);
      infos = pruned_infos;
    }
    rebase_infos->entries = infos;
    rebase_infos->length = n_slide_infos_idx;
    return rebase_infos;
  }
  if ((rebase_info = get_rebase_info(cache,
      cache->hdr->slideInfoOffset,
      cache->hdr->slideInfoSize,
      cache->maps[1].fileOffset,
      -1)) == ((void *)0))
    goto fail;
  if ((infos = calloc(1, sizeof *infos)) == ((void *)0))
    goto fail;
  infos->start = cache->maps[1].fileOffset;
  infos->end = infos->start + cache->maps[1].size;
  infos->info = rebase_info;
  rebase_infos->entries = infos;
  rebase_infos->length = 1;
  return rebase_infos;
fail_free_infos:
  free(infos);
fail:
  if (rebase_infos != ((void *)0))
    free(rebase_infos);
  return ((void *)0);
}