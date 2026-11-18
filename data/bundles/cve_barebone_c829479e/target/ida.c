GF_Err __cdecl abst_box_read(GF_Box *s, GF_BitStream *bs)
{
  char *v2; // rax
  char *v3; // rax
  u8 u8; // al
  GF_List *quality_entry_table; // [rsp+0h] [rbp-60h]
  GF_List *server_entry_table; // [rsp+8h] [rbp-58h]
  GF_AdobeFragmentRunTableBox *afrt; // [rsp+10h] [rbp-50h] BYREF
  GF_AdobeSegmentRunTableBox *asrt; // [rsp+18h] [rbp-48h] BYREF
  int j_0; // [rsp+24h] [rbp-3Ch]
  int j; // [rsp+28h] [rbp-38h]
  GF_Err e; // [rsp+2Ch] [rbp-34h]
  char *tmp_str; // [rsp+30h] [rbp-30h]
  u32 tmp_strsize; // [rsp+38h] [rbp-28h]
  int i; // [rsp+3Ch] [rbp-24h]
  GF_AdobeBootstrapInfoBox *ptr; // [rsp+40h] [rbp-20h]
  GF_BitStream *bsa; // [rsp+48h] [rbp-18h]
  GF_Box *sa; // [rsp+50h] [rbp-10h]

  sa = s;
  bsa = bs;
  ptr = (GF_AdobeBootstrapInfoBox *)s;
  if ( s->size < 0x19 )
    return -20;
  ptr->size -= 25LL;
  ptr->bootstrapinfo_version = gf_bs_read_u32(bsa);
  ptr->profile = gf_bs_read_int(bsa, 2u);
  ptr->live = gf_bs_read_int(bsa, 1u);
  ptr->update = gf_bs_read_int(bsa, 1u);
  ptr->reserved = gf_bs_read_int(bsa, 4u);
  ptr->time_scale = gf_bs_read_u32(bsa);
  ptr->current_media_time = gf_bs_read_u64(bsa);
  ptr->smpte_time_code_offset = gf_bs_read_u64(bsa);
  i = 0;
  if ( ptr->size < 8 )
    return -20;
  tmp_strsize = ptr->size;
  tmp_str = (char *)gf_malloc(tmp_strsize);
  if ( !tmp_str )
    return -2;
  memset(tmp_str, 0, tmp_strsize);
  while ( tmp_strsize )
  {
    if ( !ptr->size )
      return -20;
    --ptr->size;
    tmp_str[i] = gf_bs_read_u8(bsa);
    --tmp_strsize;
    if ( !tmp_str[i] )
      break;
    ++i;
  }
  if ( i )
    ptr->movie_identifier = gf_strdup(tmp_str);
  if ( !ptr->size )
    return -20;
  --ptr->size;
  ptr->server_entry_count = gf_bs_read_u8(bsa);
  for ( i = 0; i < ptr->server_entry_count; ++i )
  {
    j = 0;
    tmp_strsize = ptr->size;
    while ( tmp_strsize )
    {
      if ( !ptr->size )
        return -20;
      --ptr->size;
      tmp_str[j] = gf_bs_read_u8(bsa);
      --tmp_strsize;
      if ( !tmp_str[j] )
        break;
      ++j;
    }
    if ( j )
    {
      server_entry_table = ptr->server_entry_table;
      v2 = gf_strdup(tmp_str);
      des_setkey_enc_wrap(server_entry_table, v2, i);
    }
  }
  if ( !ptr->size )
    return -20;
  --ptr->size;
  ptr->quality_entry_count = gf_bs_read_u8(bsa);
  for ( i = 0; i < ptr->quality_entry_count; ++i )
  {
    j_0 = 0;
    tmp_strsize = ptr->size;
    while ( tmp_strsize )
    {
      if ( !ptr->size )
        return -20;
      --ptr->size;
      tmp_str[j_0] = gf_bs_read_u8(bsa);
      --tmp_strsize;
      if ( !tmp_str[j_0] )
        break;
      ++j_0;
    }
    if ( j_0 )
    {
      quality_entry_table = ptr->quality_entry_table;
      v3 = gf_strdup(tmp_str);
      des_setkey_enc_wrap(quality_entry_table, v3, i);
    }
  }
  i = 0;
  tmp_strsize = ptr->size;
  while ( tmp_strsize )
  {
    if ( !ptr->size )
      return -20;
    --ptr->size;
    tmp_str[i] = gf_bs_read_u8(bsa);
    --tmp_strsize;
    if ( !tmp_str[i] )
      break;
    ++i;
  }
  if ( i )
    ptr->drm_data = gf_strdup(tmp_str);
  i = 0;
  tmp_strsize = ptr->size;
  while ( tmp_strsize )
  {
    if ( !ptr->size )
      return -20;
    --ptr->size;
    tmp_str[i] = gf_bs_read_u8(bsa);
    --tmp_strsize;
    if ( !tmp_str[i] )
      break;
    ++i;
  }
  if ( i )
    ptr->meta_data = gf_strdup(tmp_str);
  if ( !ptr->size )
    return -20;
  --ptr->size;
  ptr->segment_run_table_count = gf_bs_read_u8(bsa);
  for ( i = 0; i < ptr->segment_run_table_count; ++i )
  {
    asrt = 0LL;
    e = gf_isom_box_parse((GF_Box **)&asrt, bsa);
    if ( e )
    {
      if ( asrt )
        QScopedPointerPodDeleter::cleanup((GF_Box *)asrt);
      gf_free(tmp_str);
      return e;
    }
    gf_list_add(ptr->segment_run_table_entries, asrt);
  }
  if ( !ptr->size )
    return -20;
  --ptr->size;
  u8 = gf_bs_read_u8(bsa);
  ptr->fragment_run_table_count = u8;
  for ( i = 0; ; ++i )
  {
    if ( i >= ptr->fragment_run_table_count )
    {
      gf_free(tmp_str);
      return 0;
    }
    afrt = 0LL;
    e = gf_isom_box_parse((GF_Box **)&afrt, bsa);
    if ( e )
      break;
    gf_list_add(ptr->fragment_run_table_entries, afrt);
  }
  if ( afrt )
    QScopedPointerPodDeleter::cleanup((GF_Box *)afrt);
  gf_free(tmp_str);
  return e;
}