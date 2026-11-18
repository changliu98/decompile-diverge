int __cdecl read_tfra(MOVContext *mov, AVIOContext *f)
{
  MOVFragmentIndex *v2; // rdx
  MOVFragmentIndex **fragment_index_data; // rax
  unsigned int fragment_index_count; // ecx
  int64_t offset; // [rsp+8h] [rbp-58h]
  int64_t time; // [rsp+10h] [rbp-50h]
  MOVFragmentIndex **tmp; // [rsp+18h] [rbp-48h]
  unsigned int size; // [rsp+24h] [rbp-3Ch]
  int64_t pos; // [rsp+28h] [rbp-38h]
  int j; // [rsp+30h] [rbp-30h]
  int ja; // [rsp+30h] [rbp-30h]
  int jb; // [rsp+30h] [rbp-30h]
  unsigned int i; // [rsp+34h] [rbp-2Ch]
  int fieldlength; // [rsp+38h] [rbp-28h]
  int version; // [rsp+3Ch] [rbp-24h]
  MOVFragmentIndex *index; // [rsp+40h] [rbp-20h] BYREF
  AVIOContext *fa; // [rsp+48h] [rbp-18h]
  MOVContext *mova; // [rsp+50h] [rbp-10h]

  mova = mov;
  fa = f;
  index = 0LL;
  pos = avio_tell(f);
  size = avio_rb32(f);
  if ( avio_rb32(f) != 1952871009 )
    return 1;
  av_log(mova->fc, 40, "found tfra\n");
  index = (MOVFragmentIndex *)av_mallocz(0x18uLL);
  if ( !index )
    return -12;
  tmp = (MOVFragmentIndex **)av_realloc_array(mova->fragment_index_data, mova->fragment_index_count + 1, 8uLL);
  if ( tmp )
  {
    mova->fragment_index_data = tmp;
    v2 = index;
    fragment_index_data = mova->fragment_index_data;
    fragment_index_count = mova->fragment_index_count;
    mova->fragment_index_count = fragment_index_count + 1;
    fragment_index_data[fragment_index_count] = v2;
    version = avio_r8(fa);
    avio_rb24(fa);
    index->track_id = avio_rb32(fa);
    fieldlength = avio_rb32(fa);
    index->item_count = avio_rb32(fa);
    index->items = (MOVFragmentIndexItem *)av_mallocz_array(index->item_count, 0x18uLL);
    if ( index->items )
    {
      for ( i = 0; i < index->item_count; ++i )
      {
        if ( version == 1 )
        {
          time = avio_rb64(fa);
          offset = avio_rb64(fa);
        }
        else
        {
          time = avio_rb32(fa);
          offset = avio_rb32(fa);
        }
        index->items[i].time = time;
        index->items[i].moof_offset = offset;
        for ( j = 0; j < ((fieldlength >> 4) & 3) + 1; ++j )
          avio_r8(fa);
        for ( ja = 0; ja < ((fieldlength >> 2) & 3) + 1; ++ja )
          avio_r8(fa);
        for ( jb = 0; jb < (fieldlength & 3) + 1; ++jb )
          avio_r8(fa);
      }
      avio_seek(fa, size + pos, 0);
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