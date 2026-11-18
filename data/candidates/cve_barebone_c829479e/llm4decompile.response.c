GF_Err abst_box_read(GF_Box *s, GF_BitStream *bs)
{
 int i, j;
 GF_Err e;
 char *tmp_str;
 u32 tmp_strsize;
 GF_AdobeBootstrapInfoBox *ptr;

 ptr = (GF_AdobeBootstrapInfoBox *)s;

 if (s->size < 25)
  return GF_ISOM_INVALID_FILE;

 s->size -= 25;
 ptr->bootstrapinfo_version = gf_bs_read_u32(bs);
 ptr->profile = (u8) gf_bs_read_int(bs, 2);
 ptr->live = (Bool) gf_bs_read_int(bs, 1);
 ptr->update = (Bool) gf_bs_read_int(bs, 1);
 ptr->reserved = (u8) gf_bs_read_int(bs, 4);
 ptr->time_scale = gf_bs_read_u32(bs);
 ptr->current_media_time = gf_bs_read_u64(bs);
 ptr->smpte_time_code_offset = gf_bs_read_u64(bs);

 if (ptr->size < 8)
  return GF_ISOM_INVALID_FILE;

 tmp_strsize = ptr->size;
 tmp_str = (char *) gf_malloc(sizeof(char) * tmp_strsize);
 if (!tmp_str)
  return GF_OUT_OF_MEM;
 memset(tmp_str, 0, tmp_strsize);

 i = 0;
 while (tmp_strsize) {
  if (!ptr->size)
   return GF_ISOM_INVALID_FILE;
  ptr->size -= 1;
  tmp_str[i] = gf_bs_read_u8(bs);
  tmp_strsize -= 1;
  if (tmp_str[i] == 0)
   break;
  i += 1;
 }
 if (i)
  ptr->movie_identifier = gf_strdup(tmp_str);

 if (!ptr->size)
  return GF_ISOM_INVALID_FILE;
 ptr->size -= 1;
 ptr->server_entry_count = gf_bs_read_u8(bs);

 for (i = 0; i < ptr->server_entry_count; i++) {
  j = 0;
  tmp_strsize = ptr->size;
  while (tmp_strsize) {
   if (!ptr->size)
    return GF_ISOM_INVALID_FILE;
   ptr->size -= 1;
   tmp_str[j] = gf_bs_read_u8(bs);
   tmp_strsize -= 1;
   if (tmp_str[j] == 0)
    break;
   j += 1;
  }
  if (j)
   gf_list_insert(ptr->server_entry_table, gf_strdup(tmp_str), i);
 }

 if (!ptr->size)
  return GF_ISOM_INVALID_FILE;
 ptr->size -= 1;
 ptr->quality_entry_count = gf_bs_read_u8(bs);

 for (i = 0; i < ptr->quality_entry_count; i++) {
  j = 0;
  tmp_strsize = ptr->size;
  while (tmp_strsize) {
   if (!ptr->size)
    return GF_ISOM_INVALID_FILE;
   ptr->size -= 1;
   tmp_str[j] = gf_bs_read_u8(bs);
   tmp_strsize -= 1;
   if (tmp_str[j] == 0)
    break;
   j += 1;
  }
  if (j)
   gf_list_insert(ptr->quality_entry_table, gf_strdup(tmp_str), i);
 }

 i = 0;
 tmp_strsize = ptr->size;
 while (tmp_strsize) {
  if (!ptr->size)
   return GF_ISOM_INVALID_FILE;
  ptr->size -= 1;
  tmp_str[i]