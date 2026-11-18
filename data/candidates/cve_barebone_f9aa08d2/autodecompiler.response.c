static int abst_box_read(GF_QTTrackInfo *info, GF_BitStream *bs)
{
 char *str;
 u32 len, i, j, err;
 if (info->box_size < 26) return -20;

 info->box_size -= 25;
 info->track_id = gf_bs_read_u32(bs);
 info->track_flags = (char)gf_bs_read_int(bs, 2);
 info->track_enabled = gf_bs_read_int(bs, 1);
 info->track_invisible = gf_bs_read_int(bs, 1);
 info->track_layer = (char)gf_bs_read_int(bs, 4);
 info->track_volume = gf_bs_read_u32(bs);
 info->track_width = gf_bs_read_u64(bs);
 info->track_height = gf_bs_read_u64(bs);

 i=0;
 if (info->box_size < 9) return -20;
 len = info->box_size - 8;
 str = gf_malloc(len*sizeof(char));
 if (!str) return -2;
 memset(str, 0, len*sizeof(char));

 while (len) {
  if (info->box_size<2) return -20;
  info->box_size--;
  str[i] = (char)gf_bs_read_u8(bs);
  len--;
  if (str[i] == 0) break;
  i++;
 }
 if (i) info->track_name = gf_strdup(str);

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_type = (char)gf_bs_read_u8(bs);

 i=0;
 while (i < info->track_type) {
  j=0;
  len = info->box_size;
  while (len) {
   if (info->box_size<2) return -20;
   info->box_size--;
   str[j] = (char)gf_bs_read_u8(bs);
   len--;
   if (str[j] == 0) break;
   j++;
  }
  if (j) des_setkey_enc_wrap(info->track_key, gf_strdup(str), i);
  i++;
 }

 i=0;
 len = info->box_size;
 while (len) {
  if (info->box_size<2) return -20;
  info->box_size--;
  str[i] = (char)gf_bs_read_u8(bs);
  len--;
  if (str[i] == 0) break;
  i++;
 }
 if (i) info->track_language = gf_strdup(str);

 i=0;
 len = info->box_size;
 while (len) {
  if (info->box_size<2) return -20;
  info->box_size--;
  str[i] = (char)gf_bs_read_u8(bs);
  len--;
  if (str[i] == 0) break;
  i++;
 }
 if (i) info->track_quality = gf_strdup(str);

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_num_sample_desc = (char)gf_bs_read_u8(bs);

 for (i=0; i<info->track_num_sample_desc; i++) {
  GF_QTSampleDescription *desc = NULL;
  err = gf_isom_box_parse((GF_Box **)&desc, bs);
  if (err) {
   if (desc) __ZN24QScopedPointerPodDeleter7cleanupEPv(desc);
   gf_free(str);
   return err;
  }
  gf_list_add(info->track_sample_desc, desc);
 }

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_num_chunks = (char)gf_bs_read_u8(bs);

 for (i=0; i<info->track_num_chunks; i++) {
  GF_QTChunk *chunk = NULL;
  err = gf_isom_box_parse((GF_Box **)&chunk, bs);
  if (err) {
   if (chunk) __ZN24QScopedPointerPodDeleter7cleanupEPv(chunk);
   gf_free(str);
   return err;
  }
  gf_list_add(info->track_chunks, chunk);
 }

 gf_free(str);
 return 0;
}