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
  len = abox->length - 8;
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
  abox->data_reference = gf_bs_read_u8(bs);
  for (i = 0; i < abox->data_reference; i++) {
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
    if (j != 0) des_setkey_enc_wrap(abox->data_enc, gf_strdup(str), i);
  }
  if (abox->length == 0) return -20;
  abox->length--;
  abox->data_reference_url = gf_bs_read_u8(bs);
  for (i = 0; i < abox->data_reference_url; i++) {
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
    if (j != 0) des_setkey_enc_wrap(abox->data_enc_url, gf_strdup(str), i);
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
    gf_isom_track_t *track = NULL;
    err = gf_isom_box_parse((gf_isom_box_t **)&track, bs);
    if (err) {
      if (track) {
        QScopedPointerPodDeleter::cleanup(track);
      }
      gf_free(str);
      return err;
    }
    gf_list_add(abox->tracks, track);
  }
  if (abox->length == 0) return -20;
  abox->length--;
  abox->media_header_id = gf_bs_read_u8(bs);
  for (i = 0; i < abox->media_header_id; i++) {
    gf_isom_media_header_t *media_header = NULL;
    err = gf_isom_box_parse((gf_isom_box_t **)&media_header, bs);
    if (err) {
      if (media_header) {
        QScopedPointerPodDeleter::cleanup(media_header);
      }
      gf_free(str);
      return err;
    }
    gf_list_add(abox->media_headers, media_header);
  }
  gf_free(str);
  return 0;
}