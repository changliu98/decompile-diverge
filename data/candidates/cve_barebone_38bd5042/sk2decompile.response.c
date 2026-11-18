gf_int32_t gf_avc_change_vui(gf_avc_t *avc, gf_avc_vui_t *vui) {
  gf_avc_nalu_t *nalu;
  gf_bs_t *bs = NULL;
  gf_bs_t *bs_out;
  gf_avc_sps_t sps;
  gf_avc_pps_t *pps;
  unsigned char *buf;
  unsigned int vui_size;
  unsigned int ret;
  unsigned int i;
  unsigned int len;
  memset(&sps, 0, sizeof(sps));
  sps.id = -1;
  i = 0;
  while ((nalu = gf_list_enum(avc->nalu_list, &i)) != NULL) {
    buf = NULL;
    ret = gf_avc_read_sps(nalu->data, nalu->size, &sps, NULL, &vui_size);
    if (ret < 0) {
      if (bs) gf_bs_del(bs);
      continue;
    }
    buf = (unsigned char *)gf_malloc(nalu->size - 1);
    len = gf_media_nalu_remove_emulation_bytes(nalu->data + 1, buf,
                                               nalu->size - 1);
    bs = gf_bs_new(buf, len, 0);
    gf_bs_read_data(bs, buf, len);
    gf_bs_seek(bs, 0);
    bs_out = gf_bs_new(NULL, 0, 1);
    assert(vui_size >= 8);
    while (vui_size != 8) {
      len = gf_bs_read_int(bs, 1);
      gf_bs_write_int(bs_out, len, 1);
      vui_size--;
    }
    avc_hevc_vvc_rewrite_vui(vui, bs, bs_out, 0x21);
    while (gf_bs_bits_available(bs)) {
      len = gf_bs_read_int(bs, 1);
      gf_bs_write_int(bs_out, len, 1);
    }
    gf_bs_del(bs);
    bs = NULL;
    gf_free(buf);
    gf_bs_get_content(bs_out, &buf, &len);
    len = gf_media_nalu_emulation_bytes_add_count(buf, len);
    if (len + nalu->size + 1 > nalu->size) {
      nalu->data = (unsigned char *)gf_realloc(nalu->data, len + nalu->size + 1);
    }
    nalu->size =
        gf_media_nalu_add_emulation_bytes(buf, nalu->data + 1, len) + 1;
    gf_bs_del(bs_out);
    gf_free(buf);
  }
  return 0;
}