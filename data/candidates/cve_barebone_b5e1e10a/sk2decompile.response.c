static void print_udta(gf_isom_t *gfi, int track, gf_udta_t udta) {
  int count, i, j, k, l;
  gf_fourcc_t type;
  gf_fourcc_t subtype;
  unsigned char *data;
  int data_len;
  count = gf_isom_get_udta_count(gfi, track);
  if (count == 0) return;
  if (udta != GF_UAA) {
    for (i = 0; i < count; i++) {
      gf_isom_get_udta_type(gfi, track, i + 1, &type, subtype);
      if (type == 0x69746161) {
        count--;
        break;
      }
    }
    if (count == 0) return;
  }
  fprintf(stdout, "%d UDTA types: ", count);
  for (i = 0; i < count; i++) {
    int first = 1;
    gf_isom_get_udta_type(gfi, track, i + 1, &type, subtype);
    j = gf_isom_get_user_data_count(gfi, track, type, subtype);
    fprintf(stdout, "%s (%d) ", gf_4cc_to_str(type), j);
    for (k = 0; k < j; k++) {
      data = NULL;
      gf_isom_get_user_data(gfi, track, type, subtype, k + 1, &data, &data_len);
      if (data != NULL) {
        if (gf_utf8_is_legal(data, data_len)) {
          if (first) {
            fprintf(stdout, "\n");
            first = 0;
          }
          fprintf(stdout, "\t%s\n", data);
        }
        gf_free(data);
      }
    }
  }
  fprintf(stdout, "\n");
}