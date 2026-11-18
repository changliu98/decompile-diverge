RzDyldRebaseInfos *__cdecl get_rebase_infos(RzDyldCache *cache)
{
  RzDyldRebaseInfo *rebase_info; // rax
  ut64 slide; // [rsp+0h] [rbp-110h]
  bool v4; // [rsp+Eh] [rbp-102h]
  bool v5; // [rsp+Fh] [rbp-101h]
  RzDyldRebaseInfosEntry *infos_0; // [rsp+10h] [rbp-100h]
  RzDyldRebaseInfosEntry *pruned_infos; // [rsp+18h] [rbp-F8h]
  cache_mapping_slide entry; // [rsp+28h] [rbp-E8h] BYREF
  ut64 offset; // [rsp+60h] [rbp-B0h]
  RzDyldRebaseInfo *prev_info; // [rsp+68h] [rbp-A8h]
  ut32 j; // [rsp+74h] [rbp-9Ch]
  ut64 slide_infos_offset; // [rsp+78h] [rbp-98h]
  ut32 sio; // [rsp+84h] [rbp-8Ch] BYREF
  ut64 hdr_offset_0; // [rsp+88h] [rbp-88h]
  ut32 k; // [rsp+94h] [rbp-7Ch]
  RzDyldRebaseInfosEntry *infos; // [rsp+98h] [rbp-78h]
  ut64 hdr_offset; // [rsp+A0h] [rbp-70h]
  ut32 i; // [rsp+ACh] [rbp-64h]
  ut32 n_slide_infos[16]; // [rsp+B0h] [rbp-60h] BYREF
  ut32 total_slide_infos; // [rsp+F4h] [rbp-1Ch]
  RzDyldRebaseInfos *result; // [rsp+F8h] [rbp-18h]
  RzDyldCache *cachea; // [rsp+100h] [rbp-10h]

  cachea = cache;
  result = (RzDyldRebaseInfos *)calloc(1uLL, 0x10uLL);
  if ( result )
  {
    if ( cachea->hdr->slideInfoOffset && cachea->hdr->slideInfoSize )
    {
      if ( cachea->hdr->mappingCount > 1 )
      {
        infos_0 = (RzDyldRebaseInfosEntry *)calloc(1uLL, 0x18uLL);
        if ( infos_0 )
        {
          infos_0->start = cachea->maps[1].fileOffset;
          infos_0->end = cachea->maps[1].size + infos_0->start;
          infos_0->info = get_rebase_info(
                            cachea,
                            cachea->hdr->slideInfoOffset,
                            cachea->hdr->slideInfoSize,
                            infos_0->start,
                            0xFFFFFFFFFFFFFFFFLL);
          result->entries = infos_0;
          result->length = 1LL;
          return result;
        }
      }
beach:
      free(result);
      return 0LL;
    }
    total_slide_infos = 0;
    for ( i = 0; ; ++i )
    {
      v5 = 0;
      if ( i < cachea->n_hdr )
        v5 = i < 0x10;
      if ( !v5 )
        break;
      hdr_offset = cachea->hdr_offset[i];
      if ( !rz_buf_read_le32_at(cachea->buf, hdr_offset + 316, &n_slide_infos[i]) )
        goto beach;
      total_slide_infos += n_slide_infos[i];
    }
    if ( !total_slide_infos )
      goto beach;
    infos = (RzDyldRebaseInfosEntry *)calloc(total_slide_infos, 0x18uLL);
    if ( !infos )
      goto beach;
    k = 0;
    for ( i = 0; ; ++i )
    {
      v4 = 0;
      if ( i < cachea->n_hdr )
        v4 = i < 0x10;
      if ( !v4 )
        break;
      hdr_offset_0 = cachea->hdr_offset[i];
      if ( n_slide_infos[i] )
      {
        if ( rz_buf_read_le32_at(cachea->buf, hdr_offset_0 + 312, &sio) )
        {
          slide_infos_offset = sio;
          if ( sio )
          {
            slide_infos_offset += hdr_offset_0;
            prev_info = 0LL;
            for ( j = 0; j < n_slide_infos[i]; ++j )
            {
              offset = 56LL * j + slide_infos_offset;
              if ( rz_buf_fread_at(cachea->buf, offset, (ut8 *)&entry, "6lii", 1) != 56 )
                break;
              if ( entry.slideInfoOffset && entry.slideInfoSize )
              {
                infos[k].start = hdr_offset_0 + entry.fileOffset;
                infos[k].end = entry.size + infos[k].start;
                if ( prev_info )
                  slide = prev_info->slide;
                else
                  slide = -1LL;
                rebase_info = get_rebase_info(
                                cachea,
                                hdr_offset_0 + entry.slideInfoOffset,
                                entry.slideInfoSize,
                                hdr_offset_0 + entry.fileOffset,
                                slide);
                infos[k].info = rebase_info;
                prev_info = infos[k++].info;
              }
            }
          }
        }
      }
    }
    if ( !k )
    {
LABEL_32:
      free(infos);
      goto beach;
    }
    if ( k < total_slide_infos )
    {
      pruned_infos = (RzDyldRebaseInfosEntry *)calloc(k, 0x18uLL);
      if ( !pruned_infos )
        goto LABEL_32;
      memcpy(pruned_infos, infos, 24LL * k);
      free(infos);
      infos = pruned_infos;
    }
    result->entries = infos;
    result->length = k;
    return result;
  }
  return 0LL;
}