1952871009

int __cdecl read_tfra(MOVContext *mov, AVIOContext *f)
{
  int64_t offset;
  int64_t time;
  MOVFragmentIndex **tmp;
  unsigned int size;
  int64_t pos;
  int j;
  unsigned int i;
  int fieldlength;
  int version;
  MOVFragmentIndex *index;

  pos = avio_tell(f);
  size = avio_rb32(f);
  
  if (avio_rb32(f) != MKTAG_TFRA)
    return 1;

  av_log(mov->fc, 40, "found tfra\n");

  index = (MOVFragmentIndex *)av_mallocz(0x18uLL);
  if (!index)
    return -12;

  tmp = (MOVFragmentIndex **)av_realloc_array(mov->fragment_index_data, mov->fragment_index_count + 1, 8uLL);
  if (tmp)
  {
    mov->fragment_index_data = tmp;
    mov->fragment_index_data[mov->fragment_index_count] = index;
    mov->fragment_index_count++;

    version = avio_r8(f);
    avio_rb24(f);
    index->track_id = avio_rb32(f);
    fieldlength = avio_rb32(f);
    index->item_count = avio_rb32(f);
    
    index->items = (MOVFragmentIndexItem *)av_mallocz_array(index->item_count, 0x18uLL);
    if (index->items)
    {
      for (i = 0; i < index->item_count; ++i)
      {
        if (version == 1)
        {
          time = avio_rb64(f);
          offset = avio_rb64(f);
        }
        else
        {
          time = avio_rb32(f);
          offset = avio_rb32(f);
        }
        
        index->items[i].time = time;
        index->items[i].moof_offset = offset;

        // Read and discard auxiliary data based on fieldlength bit-packing
        for (j = 0; j < ((fieldlength >> 4) & 3) + 1; ++j)
          avio_r8(f);
        for (j = 0; j < ((fieldlength >> 2) & 3) + 1; ++j)
          avio_r8(f);
        for (j = 0; j < (fieldlength & 3) + 1; ++j)
          avio_r8(f);
      }
      
      avio_seek(f, size + pos, 0);
      return 0;
    }
    else
    {
      index->item_count = 0;
      return -12;
    }
  }
  else
  {
    av_freep(&index);
    return -12;
  }
}