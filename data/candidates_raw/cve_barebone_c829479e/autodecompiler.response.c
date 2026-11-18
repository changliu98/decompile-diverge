static int parse_qt_track_info(GF_QTTrackInfo *info, GF_BitStream *bs)
{
 char *str;
 int i, j, err;
 u32 len;

 if (info->box_size < 26) return -20;
 info->box_size -= 25;

 info->track_id = gf_bs_read_u32(bs);
 info->track_flags = (char)gf_bs_read_int(bs, 2);
 info->track_enabled = gf_bs_read_int(bs, 1);
 info->track_inuse = gf_bs_read_int(bs, 1);
 info->track_priority = (char)gf_bs_read_int(bs, 4);

 info->track_time_scale = gf_bs_read_u32(bs);
 info->track_duration = gf_bs_read_u64(bs);
 info->track_start_time = gf_bs_read_u64(bs);

 i=0;
 if (info->box_size < 9) return -20;
 len = info->box_size;
 str = (char*)gf_malloc(len*sizeof(char));
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
 info->track_name_len = (char)gf_bs_read_u8(bs);

 i=0;
 while (i < info->track_name_len) {
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
  if (j) des_setkey_enc_wrap((unsigned char *)info->track_key, (unsigned char *)gf_strdup(str), i);
  i++;
 }

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_key_len = (char)gf_bs_read_u8(bs);

 i=0;
 while (i < info->track_key_len) {
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
  if (j) des_setkey_enc_wrap((unsigned char *)info->track_key2, (unsigned char *)gf_strdup(str), i);
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
 if (i) info->track_codec = gf_strdup(str);

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
 if (i) info->track_description = gf_strdup(str);

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_sample_count = (char)gf_bs_read_u8(bs);

 while (i < info->track_sample_count) {
  GF_ISOMSampleEntry *entry;
  err = gf_isom_box_parse((GF_Box **) &entry, bs);
  if (err) {
   if (entry) __ZN24QScopedPointerPodDeleter7cleanupEPv(entry);
   gf_free(str);
   return err;
  }
  gf_list_add(info->track_samples, entry);
  i++;
 }

 if (info->box_size<2) return -20;
 info->box_size--;
 info->track_sample_desc_count = (char)gf_bs_read_u8(bs);

 while (i < info->track_sample_desc_count) {
  GF_ISOMSampleDescription *desc;
  err = gf_isom_box_parse((GF_Box **) &desc, bs);
  if (err) {
   if (desc) __ZN24QScopedPointerPodDeleter7cleanupEPv(desc);
   gf_free(str);
   return err;
  }
  gf_list_add(info->track_sample_descs, desc);
  i++;
 }

 gf_free(str);
 return 0;
}