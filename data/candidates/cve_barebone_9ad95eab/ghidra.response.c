RzDyldRebaseInfos * get_rebase_infos(RzDyldCache *cache)

{
  _Bool _Var1;
  RzDyldRebaseInfos *__ptr;
  long lVar2;
  st64 sVar3;
  RzDyldRebaseInfo *pRVar4;
  RzDyldRebaseInfosEntry *pRVar5;
  ut64 local_118;
  bool local_109;
  RzDyldRebaseInfosEntry *infos_1;
  RzDyldRebaseInfosEntry *pruned_infos;
  ut64 slide;
  cache_mapping_slide entry;
  ut64 offset;
  RzDyldRebaseInfo *prev_info;
  ut32 j;
  ut64 slide_infos_offset;
  ut32 sio;
  ut64 hdr_offset_1;
  ut32 k;
  RzDyldRebaseInfosEntry *infos;
  ut64 hdr_offset;
  ut32 i;
  ut32 n_slide_infos [16];
  ut32 total_slide_infos;
  RzDyldRebaseInfos *result;
  RzDyldCache *cache_local;
  
  __ptr = calloc(1,0x10);
  if (__ptr == (RzDyldRebaseInfos *)0x0) {
    return (RzDyldRebaseInfos *)0x0;
  }
  if ((cache->hdr->slideInfoOffset == 0) || (cache->hdr->slideInfoSize == 0)) {
    total_slide_infos = 0;
    for (i = 0; local_109 = i < cache->n_hdr && i < 0x10, local_109; i = i + 1) {
      hdr_offset = cache->hdr_offset[i];
      _Var1 = rz_buf_read_le32_at(cache->buf,hdr_offset + 0x13c,n_slide_infos + i);
      if (!_Var1) goto LAB_001019fb;
      total_slide_infos = n_slide_infos[i] + total_slide_infos;
    }
    if ((total_slide_infos != 0) &&
       (infos = calloc((ulong)total_slide_infos,0x18), infos != (RzDyldRebaseInfosEntry *)0x0)) {
      k = 0;
      for (i = 0; i < cache->n_hdr && i < 0x10; i = i + 1) {
        hdr_offset_1 = cache->hdr_offset[i];
        if (((n_slide_infos[i] != 0) &&
            (_Var1 = rz_buf_read_le32_at(cache->buf,hdr_offset_1 + 0x138,&sio), _Var1)) &&
           ((ulong)sio != 0)) {
          lVar2 = hdr_offset_1 + sio;
          prev_info = (RzDyldRebaseInfo *)0x0;
          j = 0;
          while ((j < n_slide_infos[i] &&
                 (sVar3 = rz_buf_fread_at(cache->buf,lVar2 + (ulong)j * 0x38,(ut8 *)&entry,"6lii",1)
                 , sVar3 == 0x38))) {
            if ((entry.slideInfoOffset != 0) && (entry.slideInfoSize != 0)) {
              infos[k].start = entry.fileOffset + hdr_offset_1;
              infos[k].end = infos[k].start + entry.size;
              if (prev_info == (RzDyldRebaseInfo *)0x0) {
                local_118 = 0xffffffffffffffff;
              }
              else {
                local_118 = prev_info->slide;
              }
              pRVar4 = get_rebase_info(cache,entry.slideInfoOffset + hdr_offset_1,
                                       entry.slideInfoSize,entry.fileOffset + hdr_offset_1,local_118
                                      );
              infos[k].info = pRVar4;
              prev_info = infos[k].info;
              k = k + 1;
            }
            j = j + 1;
          }
        }
      }
      if (k != 0) {
        if (k < total_slide_infos) {
          pRVar5 = calloc((ulong)k,0x18);
          if (pRVar5 == (RzDyldRebaseInfosEntry *)0x0) {
            free(infos);
            goto LAB_001019fb;
          }
          memcpy(pRVar5,infos,(ulong)k * 0x18);
          free(infos);
          infos = pRVar5;
        }
        __ptr->entries = infos;
        __ptr->length = (ulong)k;
        return __ptr;
      }
      free(infos);
    }
  }
  else if ((1 < cache->hdr->mappingCount) &&
          (pRVar5 = calloc(1,0x18), pRVar5 != (RzDyldRebaseInfosEntry *)0x0)) {
    pRVar5->start = cache->maps[1].fileOffset;
    pRVar5->end = pRVar5->start + cache->maps[1].size;
    pRVar4 = get_rebase_info(cache,cache->hdr->slideInfoOffset,cache->hdr->slideInfoSize,
                             pRVar5->start,0xffffffffffffffff);
    pRVar5->info = pRVar4;
    __ptr->entries = pRVar5;
    __ptr->length = 1;
    return __ptr;
  }
LAB_001019fb:
  free(__ptr);
  return (RzDyldRebaseInfos *)0x0;
}