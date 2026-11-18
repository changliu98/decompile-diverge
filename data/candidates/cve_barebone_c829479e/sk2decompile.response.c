gf_error_t abst_box_read(gf_isom_box_t *box, gf_bs_t *bs) {
  gf_error_t err;
  abst_box_t *abox = (abst_box_t *)box;
  char *str;
  int i, j;
  unsigned int len;
  if (box->length < 25) return -20;
  abox->length -= 25;
  abox->creation_time = gf_bs_read_u32(bs);
  abox->modification_time = gf_bs_read_int(bs, 2);
  abox->timescale = gf_bs_read_int(bs, 1);
  abox->duration = gf_bs_read_int(bs, 1);
  abox->rate = gf_bs_read_int(bs, 4);
  abox->volume = gf_bs_read_u32(bs);
  abox->reserved1 = gf_bs_read_u64(bs);
  abox->reserved2 = gf_bs_read_u64(bs);
  i = 0;
  if (abox->length < 8) return -20;
  len = abox->length;
  str = gf_malloc(len);
  if (str == NULL) return -2;
  memset(str, 0, len);
  while (len > 0) {
    if (abox->length == 0) return -20;
    abox->length--;
    str[i] = gf_bs_read_u8(bs);
    len--;
    if (str[i] == '\0') break;
    i++;
  }
  if (i != 0) abox->name = gf_strdup(str);
  if (abox->length == 0) return -20;
  abox->length--;
  abox->data_reference_index = gf_bs_read_u8(bs);
  for (i = 0; i < abox->data_reference_index; i++) {
    j = 0;
    len = abox->length;
    while (len > 0) {
      if (abox->length == 0) return -20;
      abox->length--;
      str[j] = gf_bs_read_u8(bs);
      len--;
      if (str[j] == '\0') break;
      j++;
    }
    if (j != 0) des_setkey_enc_wrap(abox->data_reference_enc, gf_strdup(str), i);
  }
  if (abox->length == 0) return -20;
  abox->length--;
  abox->data_reference_url_index = gf_bs_read_u8(bs);
  for (i = 0; i < abox->data_reference_url_index; i++) {
    j = 0;
    len = abox->length;
    while (len > 0) {
      if (abox->length == 0) return -20;
      abox->length--;
      str[j] = gf_bs_read_u8(bs);
      len--;
      if (str[j] == '\0') break;
      j++;
    }
    if (j != 0)
      des_setkey_enc_wrap(abox->data_reference_url_enc, gf_strdup(str), i);
  }
  i = 0;
  len = abox->length;
  while (len > 0) {
    if (abox->length == 0) return -20;
    abox->length--;
    str[i] = gf_bs_read_u8(bs);
    len--;
    if (str[i] == '\0') break;
    i++;
  }
  if (i != 0) abox->location = gf_strdup(str);
  i = 0;
  len = abox->length;
  while (len > 0) {
    if (abox->length == 0) return -20;
    abox->length--;
    str[i] = gf_bs_read_u8(bs);
    len--;
    if (str[i] == '\0') break;
    i++;
  }
  if (i != 0) abox->data_location = gf_strdup(str);
  if (abox->length == 0) return -20;
  abox->length--;
  abox->next_track_id = gf_bs_read_u8(bs);
  for (i = 0; i < abox->next_track_id; i++) {
    gf_isom_box_t *next_track = NULL;
    err = gf_isom_box_parse((gf_isom_box_t **)&next_track, bs);
    if (err) {
      if (next_track) {
        QScopedPointerPodDeleter::cleanup(next_track);
      }
      gf_free(str);
      return err;
    }
    gf_list_add(abox->next_track, next_track);
  }
  if (abox->length == 0) return -20;
  abox->length--;
  abox->media_header_ref_index = gf_bs_read_u8(bs);
  for (i = 0; i < abox->media_header_ref_index; i++) {
    gf_isom_media_header_box_t *media_header_ref = NULL;
    err = gf_isom_box_parse((gf_isom_box_t **)&media_header_ref, bs);
    if (err) {
      if (media_header_ref) {
        QScopedPointerPodDeleter::cleanup(media_header_ref);
      }
      gf_free(str);
      return err;
    }
    gf_list_add(abox->media_header_ref, media_header_ref);
  }
  gf_free(str);
  return 0;
}