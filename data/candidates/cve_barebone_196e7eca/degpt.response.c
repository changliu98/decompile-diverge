int read_tfra(MOVContext *mov,AVIOContext *f)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int64_t iVar5;
  MOVFragmentIndex **ppMVar6;
  MOVFragmentIndexItem *pMVar7;
  int64_t offset;
  int64_t time;
  void *tmp;
  uint32_t size;
  int64_t pos;
  int j;
  int i;
  int fieldlength;
  int version;
  MOVFragmentIndex *index;
  AVIOContext *f_local;
  MOVContext *mov_local;
  int local_c;
  
  index = (MOVFragmentIndex *)0x0;
  f_local = f;
  mov_local = mov;
  iVar5 = avio_tell(f);
  uVar1 = avio_rb32(f_local);
  uVar2 = avio_rb32(f_local);
  if (uVar2 == 0x74667261) {
    av_log(mov_local->fc,0x28,"found tfra\n");
    index = av_mallocz(0x18);
    if (index == (MOVFragmentIndex *)0x0) {
      local_c = -0xc;
    }
    else {
      ppMVar6 = av_realloc_array(mov_local->fragment_index_data,
                                 (ulong)(mov_local->fragment_index_count + 1),8);
      if (ppMVar6 == (MOVFragmentIndex **)0x0) {
        av_freep(&index);
        local_c = -0xc;
      }
      else {
        mov_local->fragment_index_data = ppMVar6;
        uVar2 = mov_local->fragment_index_count;
        mov_local->fragment_index_count = uVar2 + 1;
        mov_local->fragment_index_data[uVar2] = index;
        iVar3 = avio_r8(f_local);
        avio_rb24(f_local);
        uVar2 = avio_rb32(f_local);
        index->track_id = uVar2;
        uVar2 = avio_rb32(f_local);
        uVar4 = avio_rb32(f_local);
        index->item_count = uVar4;
        pMVar7 = av_mallocz_array((ulong)index->item_count,0x18);
        index->items = pMVar7;
        if (index->items == (MOVFragmentIndexItem *)0x0) {
          index->item_count = 0;
          local_c = -0xc;
        }
        else {
          for (i = 0; (uint)i < index->item_count; i = i + 1) {
            if (iVar3 == 1) {
              time = avio_rb64(f_local);
              offset = avio_rb64(f_local);
            }
            else {
              uVar4 = avio_rb32(f_local);
              time = (int64_t)uVar4;
              uVar4 = avio_rb32(f_local);
              offset = (int64_t)uVar4;
            }
            index->items[i].time = time;
            index->items[i].moof_offset = offset;
            for (j = 0; j < (int)(((int)uVar2 >> 4 & 3U) + 1); j = j + 1) {
              avio_r8(f_local);
            }
            for (j = 0; j < (int)(((int)uVar2 >> 2 & 3U) + 1); j = j + 1) {
              avio_r8(f_local);
            }
            for (j = 0; j < (int)((uVar2 & 3) + 1); j = j + 1) {
              avio_r8(f_local);
            }
          }
          avio_seek(f_local,iVar5 + (ulong)uVar1,0);
          local_c = 0;
        }
      }
    }
  }
  else {
    local_c = 1;
  }
  return local_c;
}