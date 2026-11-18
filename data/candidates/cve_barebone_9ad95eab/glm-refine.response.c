RzDyldRebaseInfos *__cdecl get_rebase_infos(RzDyldCache *cache)
{
  RzDyldRebaseInfos *result = (RzDyldRebaseInfos *)calloc(1uLL, sizeof(RzDyldRebaseInfos));
  if ( !result )
    return NULL;

  // Legacy single slide info path
  if ( cache->hdr->slideInfoOffset && cache->hdr->slideInfoSize )
  {
    if ( cache->hdr->mappingCount > 1 )
    {
      RzDyldRebaseInfosEntry *entry = (RzDyldRebaseInfosEntry *)calloc(1uLL, sizeof(RzDyldRebaseInfosEntry));
      if ( !entry )
        goto beach;
        
      entry->start = cache->maps[1].fileOffset;
      entry->end = entry->start + cache->maps[1].size;
      entry->info = get_rebase_info(
                        cache,
                        cache->hdr->slideInfoOffset,
                        cache->hdr->slideInfoSize,
                        entry->start,
                        0xFFFFFFFFFFFFFFFFLL);
                        
      result->entries = entry;
      result->length = 1;
      return result;
    }
    goto beach;
  }

  // Modern multiple slide infos path
  ut32 n_slide_infos[16];
  ut32 total_slide_infos = 0;
  ut32 i;

  for ( i = 0; i < cache->n_hdr && i < 16; ++i )
  {
    ut64 hdr_offset = cache->hdr_offset[i];
    if ( !rz_buf_read_le32_at(cache->buf, hdr_offset + 316, &n_slide_infos[i]) )
      goto beach;
    total_slide_infos += n_slide_infos[i];
  }

  if ( !total_slide_infos )
    goto beach;

  RzDyldRebaseInfosEntry *infos = (RzDyldRebaseInfosEntry *)calloc(total_slide_infos, sizeof(RzDyldRebaseInfosEntry));
  if ( !infos )
    goto beach;

  ut32 k = 0;
  for ( i = 0; i < cache->n_hdr && i < 16; ++i )
  {
    ut64 hdr_offset_0 = cache->hdr_offset[i];
    if ( !n_slide_infos[i] )
      continue;

    ut32 sio;
    if ( !rz_buf_read_le32_at(cache->buf, hdr_offset_0 + 312, &sio) )
      continue;

    if ( !sio )
      continue;

    ut64 slide_infos_offset = hdr_offset_0 + sio;
    RzDyldRebaseInfo *prev_info = NULL;
    
    for ( ut32 j = 0; j < n_slide_infos[i]; ++j )
    {
      ut64 offset = 56LL * j + slide_infos_offset;
      cache_mapping_slide entry;
      
      if ( rz_buf_fread_at(cache->buf, offset, (ut8 *)&entry, "6lii", 1) != 56 )
        break;

      if ( entry.slideInfoOffset && entry.slideInfoSize )
      {
        infos[k].start = hdr_offset_0 + entry.fileOffset;
        infos[k].end = infos[k].start + entry.size;
        
        ut64 slide = prev_info ? prev_info->slide : 0xFFFFFFFFFFFFFFFFLL;
        infos[k].info = get_rebase_info(
                            cache,
                            hdr_offset_0 + entry.slideInfoOffset,
                            entry.slideInfoSize,
                            hdr_offset_0 + entry.fileOffset,
                            slide);
                            
        prev_info = infos[k++].info;
      }
    }
  }

  if ( !k )
  {
    free(infos);
    goto beach;
  }

  if ( k < total_slide_infos )
  {
    RzDyldRebaseInfosEntry *pruned_infos = (RzDyldRebaseInfosEntry *)calloc(k, sizeof(RzDyldRebaseInfosEntry));
    if ( !pruned_infos )
    {
      free(infos);
      goto beach;
    }
    memcpy(pruned_infos, infos, 24LL * k);
    free(infos);
    infos = pruned_infos;
  }

  result->entries = infos;
  result->length = k;
  return result;

beach:
  free(result);
  return NULL;
}